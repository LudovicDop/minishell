/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:27:41 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/25 17:34:36 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_first_node_init(t_lexer *node, t_glob *glob, int *pipe_fd)
{
	if (glob->root == node)
	{
		glob->fd_in_old = dup(STDIN_FILENO);
		if (glob->fd_in_old == -1)
			return (1);
		if (ft_is_it_pipe(glob->root))
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

int	ft_is_it_pipe(t_lexer *root)
{
	t_lexer	*current;

	if (!root)
		return (0);
	current = root;
	while (current)
	{
		if (current->type == PIPE || current->type == REDIRECT_APPEND \
		|| current->type == REDIRECT_OUT)
			return (1);
		current = current->next;
	}
	return (0);
}

int	ft_single_cmd(t_lexer *node, t_glob *glob, int *pipe_fd, t_envp **envp_list)
{
	if (node->type == CMD 
		&& ft_command_after(node) && !ft_is_it_pipe(glob->root))
	{
		// fprintf(stderr, "\033[31;1mExecute CMD (cmd : %s) --> single_cmd\033[m\n", node->value[0]);
		if (!search_builtins_token(node, envp_list, glob, pipe_fd))
			execute_command(node, pipe_fd, *envp_list, glob);
		if (dup2(glob->fd_in_old, STDIN_FILENO) == -1)
			return (1);
		ft_wait_last_cmd(glob);
		execute_ast(node->next, pipe_fd, envp_list, glob);
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
