/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:16:18 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/27 15:44:22 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int search_builtins_cmd(t_cmd *cmd)
{
    char **tmp_arg;

    fprintf(stderr, "\033[32;1mStarting search_builtins!\033[m\n");
    if (!cmd)
        return (0);
    tmp_arg = ft_split(cmd->arg, ' ');
    if (!tmp_arg)
        return (1);
    fprintf(stderr, "search builtins_cmd\n");
    if (!ft_strcmp(tmp_arg[0], "export"))
    {
        fprintf(stderr, "\033[32;1mStarting export function!\033[m\n");
        fprintf(stderr ,"\033[31;1mcmd->arg : %s\033[m\n", cmd->arg);  
        ft_export(&(cmd->envp_ref), tmp_arg[1]);
    }
    return (0);
}

