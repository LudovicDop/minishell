/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:54:53 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/26 12:15:07 by ldoppler         ###   ########.fr       */
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

void	ft_error_exec(char *error_msg, char *cmd_name)
{
	ft_putstr_fd("nemshell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_msg, 2);
}

void	execute_fail_builtins(t_glob *glob, t_envp *envp_list,
		int *pipe_fd)
{
	free(glob->prompt);
	free_lexer(glob->root);
	free_envp(&envp_list);
	ft_free_id_list(&glob->id_node);
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
	if (glob->fd_in_old)
		close(glob->fd_in_old);
	free(glob);
	exit(0);
}

int	ft_end_cmd(t_lexer *node, t_glob *glob, int *pipe_fd)
{
	if (!node || node->type == 1)
	{
		if (glob->root == NULL)
			return (1);
		ft_wait_everyone(glob);
		if (how_many_cmd(glob->root) <= 1)
		{
			if (dup2(glob->fd_in_old, STDIN_FILENO) == -1)
				return (1);
			return (close(glob->fd_in_old), 1);
		}
		if (ft_is_it_pipe(glob->root))
			return (close(pipe_fd[READ]), close(pipe_fd[WRITE]),
				close(glob->fd_in_old), 1);
		return (close(glob->fd_in_old), 1);
	}
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
