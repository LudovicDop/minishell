/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:27:41 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/15 14:33:34 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_end_cmd(t_lexer *node, t_glob *glob, int *pipe_fd)
{
    if (!node || node->type == 1)
    {
        ft_wait_everyone(glob);
        if (how_many_cmd(glob->root) <= 1)
            return (1);
        return (close(pipe_fd[READ]), close(pipe_fd[WRITE]), close(glob->fd_in_old), 1);
    }
    return (0);
}

int ft_first_node_init(t_lexer *node, t_glob *glob, int *pipe_fd)
{
    if (glob->root == node)
    {
        glob->fd_in_old = dup(STDIN_FILENO);
        if (glob->fd_in_old == -1)
            return (1);
        if (how_many_cmd(glob->root) > 1)
        {
            if (pipe(pipe_fd) < 0)
                return (1);
        }
    }
    return (0);
}