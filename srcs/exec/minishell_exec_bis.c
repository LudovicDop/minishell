/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:27:41 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/21 15:50:26 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_end_cmd(t_lexer *node, t_glob *glob, int *pipe_fd)
{
	if (!node || node->type == 1)
	{
		if (glob->root == NULL)
		{
			return (1);
		}
		ft_wait_everyone(glob);
		if (how_many_cmd(glob->root) <= 1)
		{
			dup2(glob->fd_in_old, STDIN_FILENO);
			return (close(glob->fd_in_old), 1);
		}
		return (close(pipe_fd[READ]), close(pipe_fd[WRITE]),
			close(glob->fd_in_old), 1);
	}
	return (0);
}

int	ft_first_node_init(t_lexer *node, t_glob *glob, int *pipe_fd)
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

int	ft_command_after(t_lexer *node)
{
	t_lexer	*current;

	current = node;
	if (!current)
		return (0);
	while (current)
	{
		if (current->type == CMD)
			return (1);
		current = current->next;
	}
	return (0);
}

int	ft_single_cmd(t_lexer *node, t_glob *glob, int *pipe_fd, t_envp **envp_list)
{
	if (node->type == CMD && how_many_cmd(glob->root) == 1
		&& ft_command_after(node))
	{
		if (!search_builtins_token(glob->root, envp_list, glob))
			execute_command(node, pipe_fd, *envp_list, glob);
		dup2(glob->fd_in_old, STDIN_FILENO);
		if (glob->fd_in_old == -1)
			return (1);
	}
	return (0);
}

int	how_many_cmd(t_lexer *token)
{
	int	nbre_of_cmd;

	nbre_of_cmd = 0;
	while (token)
	{
		if (token->type == CMD)
			nbre_of_cmd++;
		token = token->next;
	}
	return (nbre_of_cmd);
}
