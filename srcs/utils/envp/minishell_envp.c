/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:05:55 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/08 18:13:54 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *test_good_path_for_exec(char *exec_name, char *path)
{
    int     i;
    char    *tmp;
    char    *tmp_bis;
    char    **split_path;

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
    int i;

    i = 0;

    while ((*cmd)->tab_ref->envp[i])
    {
        if (ft_strncmp((*cmd)->tab_ref->envp[i], "PATH=", sizeof(char) * 5) == 0)
        {
            return ((*cmd)->tab_ref->envp[i] + 5);
        }
        i++;
    }
    return (NULL);
}

void    init_env_path(t_cmd **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        (cmd[i]->pathname) = test_good_path_for_exec(cmd[i]->arg[0], search_path(cmd));
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
        current = current->next;
    }
    current->next = new_node;
    
}

void    print_envp(t_envp *list)
{
    while (list)
    {
        printf("\033[32;1m%s\033[m\033[31;1m%s\033[m\n", list->key, list->value);
        list = list->next;
    }
}

void    init_envp(t_envp **envp_s, char **envp)
{
    t_envp *new_node;
    int i;

    *envp_s = NULL;
    i = 0;
    if (!envp)
        ;
    new_node = *envp_s;
    while (envp[i])
    {
        new_node = malloc(sizeof(t_envp));
        new_node->value = ft_strdup(ft_strchr(envp[i], '='));
        new_node->key = ft_strchr_reverse(envp[i], '=');
        new_node->next = NULL;
        add_node_to_envp(envp_s, new_node);
        i++;
    }
}