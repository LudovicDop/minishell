/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins_child.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:49:01 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/01 22:53:10 by ludovicdopp      ###   ########.fr       */
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
        return (1);
    else if(!ft_strcmp(tmp_arg[0], "env"))
    {
        ft_env(&(cmd->envp_ref));
        return (1);
    }
    return (0);
}