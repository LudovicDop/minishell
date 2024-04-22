/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:16:18 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/04/22 12:15:58 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_echo(t_cmd *cmd)
{
    printf("%s\n", cmd->arg[1]);
}
int search_builtins_cmd(t_cmd *cmd)
{
    if (!ft_strcmp(cmd->arg[0], "cd"))
    {
        fprintf(stderr, "\033[36;1mStarting executing cd command!\033[m\n");
        return (1);
    }
    else if (!ft_strcmp(cmd->arg[0], "echo"))
    {
        fprintf(stderr, "\033[36;1mStarting executing echo command!\033[m\n");
        ft_echo(cmd);
        return (1);
    }
    else if (!ft_strcmp(cmd->arg[0], "pwd"))
    {
        fprintf(stderr, "\033[36;1mStarting executing pwd command!\033[m\n");
        return (1);
    }
    else if (!ft_strcmp(cmd->arg[0], "export"))
    {
        fprintf(stderr, "\033[36;1mStarting executing export command!\033[m\n");
        return (1);
    }
    else if (!ft_strcmp(cmd->arg[0], "unset"))
    {
        fprintf(stderr, "\033[36;1mStarting executing unset command!\033[m\n");
        return (1);
    }
    else if (!ft_strcmp(cmd->arg[0], "env"))
    {
        fprintf(stderr, "\033[36;1mStarting executing env command!\033[m\n");
        return (1);
    }
    else if (!ft_strcmp(cmd->arg[0], "exit"))
    {
        fprintf(stderr, "\033[36;1mStarting executing exit command!\033[m\n");
        return (1);
    }
    return (0);
}
