/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_special_carac.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:30:32 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/04/21 18:54:11 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    special_carac(t_cmd *cmd)
{
    printf("lenght : %zu\n", ft_strlen(cmd->arg_redirection[0]));
    if (!ft_strcmp(cmd->arg_redirection[0], ">"))
    {
        printf("\033[32;1m>\033[m\n");
        int fd = open(cmd->arg_redirection[1], O_RDONLY | O_WRONLY | O_CREAT, 0644);
        dup2(cmd->tab_ref->pipe_fd[1], STDOUT_FILENO);
        dup2(fd, STDOUT_FILENO);
    }
    else if (!ft_strcmp(cmd->arg_redirection[0], ">>"))
    {
        printf("\033[32;1m>>\033[m\n");
        int fd = open(cmd->arg_redirection[1], O_RDONLY | O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(cmd->tab_ref->pipe_fd[1], STDOUT_FILENO);
        dup2(fd, STDOUT_FILENO);
    }
}