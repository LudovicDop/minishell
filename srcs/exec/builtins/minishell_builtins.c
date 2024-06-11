/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:16:18 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/11 16:34:58 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int search_builtins_cmd(t_cmd *cmd)
{
    char **tmp_arg;

    if (!cmd)
        return (0);
    tmp_arg = ft_split(cmd->arg, ' ');
    if (!tmp_arg)
        return (1);
    if (!ft_strcmp(tmp_arg[0], "export"))
    {
        ft_export(&(cmd->envp_ref), tmp_arg[1]);
        free_tab((void**)tmp_arg);
        return (1);
    }
    else if (!ft_strcmp(tmp_arg[0], "cd"))
    {
        ft_cd(&(cmd->envp_ref), tmp_arg[1]);
        free_tab((void**)tmp_arg);
        return (1);
    }
    else if(!ft_strcmp(tmp_arg[0], "env"))
    {
        free_tab((void**)tmp_arg);
        return (1);
    }
    else if (!ft_strcmp(tmp_arg[0], "pwd"))
    {
        free_tab((void**)tmp_arg);
        return (1);
    }
    else if (!ft_strcmp(tmp_arg[0], "unset"))
    {
        ft_unset(&(cmd->envp_ref), tmp_arg[1]);
        free_tab((void**)tmp_arg);
        return (1);
    }
    else if (!ft_strcmp(tmp_arg[0], "pwd"))
    {
        free_tab((void**)tmp_arg);
        return (1);
    }
    free_tab((void**)tmp_arg);
    return (0);
}

