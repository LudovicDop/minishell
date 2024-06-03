/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:36:43 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/03 19:41:47 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     nbre_node(t_pwd **pwd_list)
{
    t_pwd *current;
    int i;

    i = 0;
    current = *pwd_list;
    if (!current)
        return (0);
    while (current)
    {
        i++;
        current = current->next;
    }
    return (i);
}
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

void    ft_add_pwd_node(t_pwd **pwd_lst, t_pwd *node)
{
    t_pwd *tmp_lst;

    tmp_lst = *pwd_lst;
    if (!(*pwd_lst))
    {
        *pwd_lst = node;
        return ;
    }
    while (tmp_lst->next)
    {
        tmp_lst = tmp_lst->next;
    }
    tmp_lst->next = node;
    node->next = NULL;
    return ;
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
    fprintf(stderr ,"str : %s (%zu)\n", pwd_value, ft_strlen(pwd_value));
    while (pwd_value[i])
    {
        if (pwd_value[i] && pwd_value[i] == '/')
        {
            i++;
            new_node = malloc(sizeof(t_pwd));
            new_node->node = ft_strdup(pwd_until_slash(pwd_value + i));
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

void    init_pwd_w_envp(t_envp **envp, t_pwd **pwd_lst)
{
    t_pwd *current;
    char *new_pwd;

    current = *pwd_lst;
    new_pwd = ft_strdup("");
    if (!current)
        return ;
    // fprintf("current address : %p\n", current);
    // fprintf(stderr ,"\033[32;1mCurrent->node : %s (address : %p)\033[m\n", current->node, current->node);
    while (current)
    {
        new_pwd = ft_strjoin2(new_pwd, current->node);
        current = current->next;
    }
    search_key_and_replace_it(envp, "PWD", new_pwd);
    free(new_pwd);
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
void    remove_last_node_pwd(t_pwd **pwd_list)
{
    t_pwd *current;
    t_pwd *tmp;

    current = *pwd_list;
    tmp = NULL;
    if (!current)
    {
        fprintf(stderr, "finito\n");
        return ;
    }
    while (current->next)
    {
        tmp = current;
        current = current->next;
    }
    if (tmp)
    {
        fprintf(stderr ,"\033[31;1mRemove slash from node : %s\033[m\n", tmp->node);
        remove_slash(&tmp);
        tmp->next = NULL;
    }
    fprintf(stderr ,"\033[31;1mFreeing : %s (%p)\033[m\n", current->node, current->node);
    free(current->node);
    free(current);
    current = NULL;
}

char    *remove_backslash_at_end(char *pwd)
{
    int     i;
    int     j;
    char *new_string;

    i = 0;
    j = 0;
    if (!pwd)
        return (NULL);
    new_string = pwd;
    while (pwd[i] != '/')
        i++;
    new_string = malloc(sizeof(char) * i + 1);
    if (!new_string)
        return (NULL);
    while (j < i)
    {
        new_string[j] = pwd[j];
        j++;
    }
    new_string[j] = '\0';
    return (free(pwd), new_string);
}
void    ft_cd(t_envp **envp, char *path)
{
    t_pwd *pwd_lst;
    t_pwd *new_node;
    
    pwd_lst = NULL;
    new_node = NULL;
    parse_pwd(&pwd_lst, search_value_envp(envp, "PWD"));
    if (chdir(path) < 0)
    {
        perror("chdir");
        return ;
    }
    if (!ft_strcmp(path, ".."))
    {
        remove_last_node_pwd(&pwd_lst);
        init_pwd_w_envp(envp, &pwd_lst);
        return ;
    }
    else if (!ft_strcmp(path, "."))
    {
        return ;
    }
    new_node = malloc(sizeof(t_pwd));
    new_node->node = ft_strjoin("/", remove_backslash_at_end(path));
    new_node->next = NULL;
    ft_add_pwd_node(&pwd_lst, new_node);
    init_pwd_w_envp(envp, &pwd_lst);
}