/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:05:55 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/21 16:20:21 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *test_good_path_for_exec(char *exec_name, char *path)
{
    int     i;
    char    *tmp;
    char    *tmp_bis;
    char    **split_path;
    
    if (access(exec_name, F_OK) == 0)
    {
        return (exec_name);
    }
    split_path = ft_split(path, ':');
    i = 0;
    while (split_path[i])
    {
        tmp_bis = ft_strjoin(split_path[i], "/");
        tmp = ft_strjoin(tmp_bis, exec_name);
        if (access(tmp, F_OK) == 0)
        {
            free(tmp_bis);
            free_tab((void**)split_path);
            return (tmp);
        }
        free(tmp_bis);
        free(tmp);
        i++;
    }
    free_tab((void**)split_path);
    return (NULL);
}

char    *search_path(t_cmd **cmd)
{
    while ((*cmd)->tab_ref->envp)
    {
        if (!ft_strncmp((*cmd)->tab_ref->envp->key, "PATH", sizeof(char) * 5))
        {
            return ((*cmd)->tab_ref->envp->value);
        }
        (*cmd)->tab_ref->envp = (*cmd)->tab_ref->envp->next;
    }
}

void    init_env_path(t_cmd **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        // (cmd[i]->pathname) = test_good_path_for_exec(cmd[i]->arg[0], search_path(cmd));
        i++;
    }
}

void    add_node_to_envp(t_envp **list, t_envp *new_node)
{
    t_envp *current;

    if (*list == NULL)
    {
        *list = new_node;
        return ;
    }
    current = *list;
    while (current->next)
    {
        //printf("la\n");
        current = current->next;
    }
    current->next = new_node;
    
}

void    init_envp(t_envp **envp_list, char **envp)
{
    int     i;
    t_envp *current;
    t_envp *new_node;

    i = 0;
    current = *envp_list;
    while (envp[i])
    {
        new_node = malloc(sizeof(t_envp));
        if (!new_node)
            return ;
        new_node->value = ft_strdup(ft_strchr(envp[i], '='));
        new_node->key = ft_strchr_reverse(envp[i], '=');
        new_node->next = NULL;
        add_node_to_envp(envp_list, new_node);
        i++;  
    }
}
