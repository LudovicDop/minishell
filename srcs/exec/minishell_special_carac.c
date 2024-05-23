/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_special_carac.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:30:32 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/23 13:19:25 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    special_carac(t_cmd *cmd)
{

    // fprintf(stderr, "Arg_redirection : %s\n", cmd->arg_redirection);
    // if (!ft_strcmp(tmp_arg[0], ">"))
    // {
    //     printf("\033[32;1m>\033[m\n");
    //     int fd = open(tmp_arg[1], O_RDONLY | O_WRONLY | O_CREAT, 0644);
    //     dup2(cmd->tab_ref->pipe_fd[1], STDOUT_FILENO);
    //     dup2(fd, STDOUT_FILENO);
    // }
    // else if (!ft_strcmp(cmd->arg_redirection[0], ">>"))
    // {
    //     printf("\033[32;1m>>\033[m\n");
    //     int fd = open(cmd->arg_redirection[1], O_RDONLY | O_WRONLY | O_CREAT | O_APPEND, 0644);
    //     dup2(cmd->tab_ref->pipe_fd[1], STDOUT_FILENO);
    //     dup2(fd, STDOUT_FILENO);
    // }
}