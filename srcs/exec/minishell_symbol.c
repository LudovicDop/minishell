/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_symbol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 01:49:43 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/30 01:52:44 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_or(t_lexer *node, t_glob *glob, int *pipe_fd, t_envp **envp)
{
	int	tmp;

	tmp = -1;
	if (node->type == OR)
	{
		ft_wait_everyone(glob);
		ft_free_id_list(&glob->id_node);
		tmp = execute_and(node, glob);
		if (tmp == 0)
			return (execute_ast(skip_until_next_symbol(node->next), \
			pipe_fd, envp, glob), 1);
		else if (tmp == 1)
		{
			glob->last_cmd = node->next;
			if (ft_is_it_pipe(glob->last_cmd))
			{
				close(pipe_fd[WRITE]);
				close(pipe_fd[READ]);
			}
			if (dup2(glob->fd_in_old, STDIN_FILENO) == -1)
				return (1);
			return (0);
		}
	}
	return (0);
}

int	ft_and(t_lexer *node, t_glob *g, int *pipe_fd, t_envp **envp)
{
	int	tmp;

	tmp = -1;
	if (node->type == AND)
	{
		ft_wait_everyone(g);
		ft_free_id_list(&g->id_node);
		tmp = execute_and(node, g);
		if (tmp == 1)
			return (close(g->fd_in_old), ft_end_cmd(NULL, g, pipe_fd, envp), 1);
		else if (tmp == 0)
		{
			g->last_cmd = node->next;
			if (ft_is_it_pipe(g->last_cmd))
			{
				close(pipe_fd[WRITE]);
				close(pipe_fd[READ]);
			}
			if (dup2(g->fd_in_old, STDIN_FILENO) == -1)
				return (1);
			close(g->fd_in_old);
			return (0);
		}
	}
	return (0);
}

t_lexer	*skip_until_next_symbol(t_lexer *node)
{
	if (!node)
		return (NULL);
	while (node)
	{
		if (node->type == AND || node->type == OR)
			return (node);
		node = node->next;
	}
	return (node);
}

void	ft_close_norm(int *pipe_fd)
{
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
}
