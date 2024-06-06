/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_child.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:49:01 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/06 16:14:51 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int search_builtins_child(t_cmd *cmd)
{
    char **tmp_arg;

    if (!cmd)
        return (0);
    tmp_arg = ft_split(cmd->arg, ' ');
    if (!tmp_arg)
        return (1);
    if (!ft_strcmp(tmp_arg[0], "export"))
        return (1);
    else if (!ft_strcmp(tmp_arg[0], "cd"))
    {
        free_tab((void**)tmp_arg);
        return (1);
    }
    else if(!ft_strcmp(tmp_arg[0], "env"))
    {
        ft_env(&(cmd->envp_ref));
        free_tab((void**)tmp_arg);
        return (1);
    }
    else if (!ft_strcmp(tmp_arg[0], "pwd"))
    {
        ft_pwd(&cmd);
        free_tab((void**)tmp_arg);
        return (1);
    }
    free_tab((void**)tmp_arg);
    return (0);
}