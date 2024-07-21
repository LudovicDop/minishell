/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:08:25 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/21 23:40:17 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*ft_skip_heredoc(t_lexer *node)
{
	t_lexer	*current;

	if (!node)
		return (NULL);
	current = node;
	while (current)
	{
		if (current->type != HEREDOC)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	ft_heredoc_init(t_lexer *node, int *pipe_fd, char **full_string,
		char **tmp)
{
	if (!node->next || node->next->type != HEREDOC)
	{
		close(pipe_fd[READ]);
		write(pipe_fd[WRITE], *full_string, ft_strlen(*full_string));
		close(pipe_fd[WRITE]);
		free(*full_string);
		free(*tmp);
		*tmp = NULL;
	}
	else
	{
		free(*full_string);
		free(*tmp);
		*tmp = NULL;
		*full_string = NULL;
	}
}

int	ft_heredoc_child(t_lexer *node, int *pipe_fd, t_glob *glob)
{
	char	*tmp;
	char	*full_string;

	tmp = NULL;
	full_string = NULL;
	ft_heredoc_signal();
	while (node && node->type == HEREDOC)
	{
		write(1, "> ", 2);
		tmp = get_next_line(STDIN_FILENO);
		if (tmp && (ft_strncmp(node->value[0], tmp, ft_strlen(tmp) - 1) != 0
				|| ft_strcmp(tmp, "\n") == 0))
			ft_heredoc_stock_string(&tmp, &full_string);
		else if (tmp == NULL || tmp[0] == '\0')
			return (ft_norm(pipe_fd, tmp, full_string), ft_heredoc_free(node,
					glob, true), exit(0), 1);
		else if (ft_strlen(tmp) > 1 && ft_strncmp(node->value[0], tmp,
				ft_strlen(tmp) - 1) == 0)
		{
			ft_heredoc_init(node, pipe_fd, &full_string, &tmp);
			ft_heredoc_free(node, glob, false);
			node = node->next;
		}
	}
	exit(EXIT_SUCCESS);
}

int	ft_heredoc_parent(int *pipe_fd, int id, t_lexer *node, int old_stdin)
{
	close(pipe_fd[WRITE]);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	waitpid(id, 0, 0);
	if (dup2(pipe_fd[READ], STDIN_FILENO) == -1)
		return (close(pipe_fd[READ]), 1);
	close(pipe_fd[READ]);
	if (ft_empty_after_heredoc(node) == false)
	{
		close(old_stdin);
		if (pipe(pipe_fd) < 0)
			return (exit(EXIT_FAILURE), 1);
	}
	if (ft_empty_after_heredoc(node) == true)
	{
		if (dup2(old_stdin, STDIN_FILENO) == -1)
			return (exit(EXIT_FAILURE), 1);
		close(old_stdin);
	}
	return (0);
}

int	ft_heredoc(t_lexer *node, int *pipe_fd, t_glob *glob, t_envp *envp_list)
{
	int		old_stdin;
	pid_t	id;

	if (!node || node->type != HEREDOC)
		return (0);
	if (pipe(pipe_fd) < 0)
		return (1);
	id = fork();
	if (id < 0)
		return (close(pipe_fd[WRITE]), close(pipe_fd[READ]), 1);
	if (id == 0)
		ft_heredoc_child(node, pipe_fd, glob);
	else
	{
		old_stdin = dup(STDIN_FILENO);
		if (old_stdin == -1)
			return (close(pipe_fd[WRITE]), close(pipe_fd[READ]), 1);
		ft_heredoc_parent(pipe_fd, id, node, old_stdin);
		return (execute_ast(ft_skip_heredoc(node), pipe_fd, &envp_list, glob),
			1);
	}
	return (0);
}
