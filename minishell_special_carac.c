/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_special_carac.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:30:32 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/04/20 14:55:22 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    special_carac(t_cmd *cmd)
{
    if (ft_strncmp(cmd->arg_redirection[0], "<", sizeof(ft_strlen(cmd->arg_redirection[0]))))
    {
        int fd = open(cmd->arg_redirection[1], O_RDONLY | O_WRONLY | O_CREAT, 0644);
        dup2(cmd->tab_ref->pipe_fd[1], STDOUT_FILENO);
        dup2(fd, STDOUT_FILENO);
    }
}