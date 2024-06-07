/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:36:43 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/07 16:20:26 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char    *get_key(t_envp **envp, char *key)
{
    t_envp *envp_tmp;

    envp_tmp = *envp;
    while (envp_tmp)
    {
        if (!ft_strcmp(envp_tmp->key, key))
        {
            return (envp_tmp->value);
        }
        envp_tmp = envp_tmp->next; 
    }
    return (NULL);
}

char *pwd_until_slash(char *pwd)
{
    char *ret;
    int i;
    int j;

    i = 0;
    j = 0;
    if (!pwd)
        return (NULL);
    while (pwd[j] && pwd[j] != '/')
        j++;
    ret = malloc(sizeof(char) * j + 2);
    while (pwd[i])
    {
        ret[i] = pwd[i];
        if (pwd[i] == '/')
        {
            i++;
            ret[i] = '\0';
            return (ret);
        }
        i++;
    }
    ret[i] = '\0';
    return (ret);
}
void    parse_pwd(t_pwd **pwd_lst, char *pwd_value)
{
    int i;
    char  *tmp;
    t_pwd *new_node;
    
    i = 0;
    new_node = malloc(sizeof(t_pwd));
    new_node->node = ft_strdup("/");
    new_node->next = NULL;
    ft_add_pwd_node(pwd_lst, new_node);
    while (pwd_value[i])
    {
        if (pwd_value[i] && pwd_value[i] == '/')
        {
            i++;
            new_node = malloc(sizeof(t_pwd));
            new_node->node = pwd_until_slash(pwd_value + i);
            new_node->next = NULL;
            new_node->root = false;
            ft_add_pwd_node(pwd_lst, new_node);
        }
        if (pwd_value[i])
            i++;
    }
    
}

char *search_value_envp(t_envp **envp, char *key)
{
    t_envp *current;

    current = *envp;
    while (current)
    {
        if (!ft_strcmp(current->key, key))
        {
            return (current->value);
        }
        current = current->next;
    }
    return (NULL);
}

void    stock_linked_to_env(t_envp **envp, t_pwd **pwd_lst)
{
    t_pwd *current;
    char *tmp;

    tmp = ft_strdup("");
    current = *pwd_lst;
    if (!current)
        return ;
    while (current)
    {
        tmp = ft_strjoin2(tmp, current->node);
        search_key_and_replace_it(envp, "PWD", tmp);
        current = current->next;
    }
}

void    remove_slash(t_pwd **pwd_node)
{
    t_pwd *current;
    int i;

    current = *pwd_node;
    if (!current)
        return ;
    i = ft_strlen(current->node);
    if (i > 1 && current->node[i - 1] == '/')
    {
        current->node[i - 1] = '\0';
    }
    return ;
}

int is_symbolic_link(const char *path) {
    struct stat path_stat;
    
    // Use lstat to get the information about the path
    printf("\033[36;1mString : %s\033[m\n", path);
    if (lstat(path, &path_stat) != 0) {
        printf("\033[31;1mError (string : %s)\033[m\n", path);
        return -1; // Error occurred
    }

    // Check if the path is a symbolic link
    if (S_ISLNK(path_stat.st_mode)) {
        return 1; // The path is a symbolic link
    } else {
        return 0; // The path is not a symbolic link
    }
    printf("Weirdo\n");
}
void    ft_cd(t_envp **envp, char *path)
{
    char *tmp;
    t_pwd *pwd_lst;
    t_pwd *new_node;
    
    pwd_lst = NULL;
    new_node = NULL;
    if (!path || path[0] == '~')
    {
        home_path(path, envp);
        return ;
    }
    if (path[0] == '/')
    {
        absolute_path(path, &pwd_lst, envp);
        free_pwd_lst(&pwd_lst);
        return ;
    }
    parse_pwd(&pwd_lst, search_value_envp(envp, "PWD"));
    if (chdir(path) < 0)
    {
        perror("chdir");
        free_pwd_lst(&pwd_lst);
        return ;
    }
    if (!ft_strcmp(path, ".."))
    {
        remove_last_node_pwd(&pwd_lst);
        init_pwd_w_envp(envp, &pwd_lst);
        free_pwd_lst(&pwd_lst);
        return ;
    }
    printf("string : %s\n", path);
    new_node = malloc(sizeof(t_pwd));
    tmp = ft_strtrim(path, "./");
    if (tmp[0] != '\0')
        new_node->node = ft_strjoin("/", tmp);
    else
    {
        free_pwd_lst(&pwd_lst);
        pwd_lst = NULL;
        new_node->node = getcwd(0, 0);
    }
    printf("string : %s\n", tmp);
    new_node->next = NULL;
    if (is_symbolic_link(path) == 1)
    {
        printf("\033[32;1mIt is a symbolic link\033[m\n");
        ft_add_pwd_node(&pwd_lst, new_node);
        init_pwd_w_envp(envp, &pwd_lst);
    }
    else if (is_symbolic_link(path) <= 0)
    {
        printf("\033[31;1mIt is not a symbolic link\033[m\n");
        search_key_and_replace_it(envp, "PWD", getcwd(0, 0));
    }
    free_pwd_lst(&pwd_lst);
    free(tmp);
}