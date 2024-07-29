/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:53:12 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/29 16:06:04 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_red_in_result(int *pipe_fd, t_lexer *node, t_envp *envp_list,
		t_glob *glob)
{
	if (pipe(pipe_fd) == -1)
		return (1);
	close(pipe_fd[WRITE]);
	if (dup2(pipe_fd[READ], STDIN_FILENO) < 0)
		return (1);
	return (execute_ast(ft_skip_to_next_cmd(node), pipe_fd, &envp_list, glob),
		1);
}

int	ft_redirection(t_lexer *node, int *pipe_fd, t_glob *glob, t_envp *envp_list)
{
	int	i;

	i = 0;
	if (node->type >= 6 && node->type <= 9)
	{
		if (glob->root == node)
			i = 1;
		ft_red_out(node, i);
		ft_red_append(node, i);
		if (ft_red_in(node))
		{
			close(pipe_fd[READ]);
			close(pipe_fd[WRITE]);
			if (how_many_cmd(glob->root) > 1)
				return (ft_red_in_result(pipe_fd, node, envp_list, glob));
			else
				if (dup2(glob->fd_in_old, STDIN_FILENO) == -1)
					return (close(glob->fd_in_old), 1);
			return (execute_ast(ft_skip_to_next_cmd(node), pipe_fd, &envp_list,
					glob), 1);
		}
		if (ft_heredoc(node, pipe_fd, glob, envp_list))
			return (close(pipe_fd[READ]), close(pipe_fd[WRITE]), 1);
	}
	return (0);
}
