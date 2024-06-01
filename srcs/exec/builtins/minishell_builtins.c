/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:16:18 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/01 20:09:28 by ludovicdopp      ###   ########.fr       */
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
    }
    else if (!ft_strcmp(tmp_arg[0], "cd"))
    {
        ft_cd(&(cmd->envp_ref), tmp_arg[1]);
    }
    return (0);
}

