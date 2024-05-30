/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:36:43 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/30 16:14:39 by ldoppler         ###   ########.fr       */
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

void    parse_pwd(t_pwd *pwd_lst,char *pwd_value)
{
    fprintf(stderr, "\033[32;1mPWD : %s\033[m\n", pwd_value);
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

void    ft_cd(t_envp **envp, char *path)
{
    t_pwd *pwd_lst;
    t_envp *pwd;
    
    pwd_lst = NULL;
    parse_pwd(pwd_lst, search_value_envp(envp, "PWD"));
    if (chdir(path) < 0)
    {
        perror("chdir");
        return ;
    }
    search_key_and_replace_it(envp, "PWD", ft_strjoin(get_key(envp, "PWD"), ft_strjoin("/", path)));
}