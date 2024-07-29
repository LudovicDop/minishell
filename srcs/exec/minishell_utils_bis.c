/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:54:53 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/29 18:02:06 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*ft_skip_to_next_cmd(t_lexer *node)
{
	t_lexer	*current;

	current = node;
	if (!node)
		return (NULL);
	while (current && current->type != PIPE && current->type != AND)
	{
		current = current->next;
	}
	if (current)
	{
		if (current->type != AND)
			current = current->next;
	}
	return (current);
}

void	execute_fail_builtins(t_glob *glob, t_envp *envp_list, int *pipe_fd)
{
	free(glob->prompt);
	free_lexer(glob->root);
	free_envp(&envp_list);
	ft_free_id_list(&glob->id_node);
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
	close(glob->fd_in_old);
	free(glob);
	exit(0);
}

int	ft_and(t_lexer *node, t_glob *glob, int *pipe_fd, t_envp **envp)
{
	int	tmp;

	tmp = -1;
	if (node->type == AND)
	{
		ft_wait_everyone(glob);
		ft_free_id_list(&glob->id_node);
		tmp = execute_and(node, glob);
		if (tmp == 1)
			return (close(glob->fd_in_old), ft_end_cmd(NULL, glob, pipe_fd, envp), 1);
		else if (tmp == 0)
		{
			glob->last_cmd = node->next;
			if (ft_is_it_pipe(glob->last_cmd))
			{
				close(pipe_fd[WRITE]);
				close(pipe_fd[READ]);
			}
			if (dup2(glob->fd_in_old, STDIN_FILENO) == -1)
				return (1);
			close(glob->fd_in_old);
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
			return (node->next);
		node = node->next;
	}
	fprintf(stderr, "RET\n");
	return (node);
}

int	ft_or(t_lexer *node, t_glob *glob, int *pipe_fd, t_envp **envp)
{
	int	tmp;

	tmp = -1;
	fprintf(stderr, "START OR\n");
	if (node->type == OR)
	{
		ft_wait_everyone(glob);
		ft_free_id_list(&glob->id_node);
		tmp = execute_and(node, glob);
		if (tmp == 0)
		{
			fprintf(stderr, "THERE\n");
			close(glob->fd_in_old);
			execute_ast(skip_until_next_symbol(node), pipe_fd, envp, glob);
			return (1);
		}
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
			close(glob->fd_in_old);
			return (0);
		}
	}
	return (0);
}

int	ft_end_cmd(t_lexer *node, t_glob *glob, int *pipe_fd, t_envp **envp)
{
	if (!node || node->type == 1)
	{
		ft_wait_everyone(glob);
		if (!node || node->type == 1)
		{
			if (glob->root == NULL)
				return (1);
			if (how_many_cmd(glob->last_cmd) <= 1)
			{
				if (dup2(glob->fd_in_old, STDIN_FILENO) == -1)
					return (1);
				return (close(glob->fd_in_old), 1);
			}
			if (ft_is_it_pipe(glob->last_cmd))
			{
				close(pipe_fd[READ]);
				close(pipe_fd[WRITE]);
			}
			return (close(glob->fd_in_old), 1);
		}
	}
	if (ft_and(node, glob, pipe_fd, envp))
		return (1);
	if (ft_or(node, glob, pipe_fd, envp))
		return (1);
	return (0);
}

void	execute_fail(t_glob *glob, t_lexer *token, t_envp *envp_list,
		int *pipe_fd)
{
	ft_error_exec("command not found\n", token->value[0]);
	free(glob->prompt);
	free_lexer(glob->root);
	free_envp(&envp_list);
	ft_free_id_list(&glob->id_node);
	if (pipe_fd[0])
		close(pipe_fd[READ]);
	if (pipe_fd[1])
		close(pipe_fd[WRITE]);
	if (glob->fd_in_old)
		close(glob->fd_in_old);
	free(glob);
	exit(EXIT_FAILURE);
}
