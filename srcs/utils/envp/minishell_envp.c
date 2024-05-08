/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:05:55 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/04 11:09:28 by ludovicdopp      ###   ########.fr       */
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