/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:16:18 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/12 22:24:59 by ludovicdopp      ###   ########.fr       */
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
        ft_cd(cmd, &(cmd->envp_ref), tmp_arg[1]);
        free_tab((void**)tmp_arg);
        return (1);
    }
    else if(!ft_strcmp(tmp_arg[0], "env"))
    {
        ft_env(&(cmd->envp_ref));
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
        ft_pwd(&cmd);
        free_tab((void**)tmp_arg);
        return (1);
    }
    else if (!ft_strcmp(tmp_arg[0], "exit"))
    {
        ft_exit(cmd, tmp_arg[1]);
        free_tab((void**)tmp_arg);
        return (1);
    }
    else if (!ft_strcmp(tmp_arg[0], "echo"))
    {
        if (tmp_arg[1] && !ft_strcmp(tmp_arg[1], "-n"))
            ft_echo(tmp_arg[2], true, &(cmd->envp_ref));
        else
            ft_echo(tmp_arg[1], false, &(cmd->envp_ref));
        free_tab((void**)tmp_arg);
        return (1);
    }
    free_tab((void**)tmp_arg);
    return (0);
}

