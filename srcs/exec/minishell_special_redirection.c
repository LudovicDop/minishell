/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_special_redirection.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:30:32 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/26 01:05:32 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    special_carac(t_cmd *cmd)
{
    int fd;

    fprintf(stderr, "Arg_redirection : %s\n", cmd->arg_redirection);
    if (!ft_strncmp(cmd->arg_redirection, ">", 1))
    {
        cmd->arg_redirection++;
        fprintf(stderr, "=> %s\n", cmd->arg_redirection);
        fd = open(cmd->arg_redirection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror("open");
        }
        dup2(fd, STDOUT_FILENO);
    }
}