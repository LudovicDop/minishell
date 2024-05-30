/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:36:43 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/30 23:00:47 by ldoppler         ###   ########.fr       */
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

void    ft_add_pwd_node(t_pwd **pwd_lst, t_pwd *node)
{
    t_pwd *tmp_lst;

    tmp_lst = *pwd_lst;
    if (!(*pwd_lst))
    {
        fprintf(stderr, "\033[36;1mBegin linked list\033[m\n");
        *pwd_lst = node;
        return ;
    }
    while (tmp_lst->next)
    {
        tmp_lst = tmp_lst->next;
    }
    tmp_lst->next = node;
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
    fprintf(stderr, "\033[36;1mfunction : %s\033[m\n", pwd);
    while (pwd[j] && pwd[j] != '/')
        j++;
    fprintf(stderr, "j = %d\n", j + 2);
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
    fprintf(stderr, "\033[32;1mPWD : %s\033[m\n", pwd_value);
    while (pwd_value[i])
    {
        if (pwd_value[i] == '/')
        {
            i++;
            fprintf(stderr, "\033[31;1mstring : %s\033[m\n", pwd_value);
            new_node = malloc(sizeof(t_pwd));
            new_node->node = ft_strdup(pwd_until_slash(pwd_value + i));
            new_node->next = NULL;
            new_node->root = false;
            ft_add_pwd_node(pwd_lst, new_node);
        }
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
        fprintf(stderr, "TEST\n");
        tmp = ft_strjoin2(tmp, current->node);
        fprintf(stderr ,"==> %s\n", tmp);
        search_key_and_replace_it(envp, "PWD", tmp);
        current = current->next;
    }
}
void    ft_cd(t_envp **envp, char *path)
{
    t_pwd *pwd_lst;
    
    pwd_lst = NULL;
    parse_pwd(&pwd_lst, search_value_envp(envp, "PWD"));
    stock_linked_to_env(envp, &pwd_lst);
    if (chdir(path) < 0)
    {
        perror("chdir");
        return ;
    }
    /*bug ici*/
   // search_key_and_replace_it(envp, "PWD", ft_strjoin(search_value_envp(envp, "PWD"), path));
}