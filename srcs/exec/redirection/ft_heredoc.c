/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:08:25 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/20 21:48:20 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc_free(t_lexer *node, t_glob *glob)
{
	if (!node->next || (node->next && node->next->type != HEREDOC))
	{
		free(glob->prompt);
		close(glob->fd_in_old);
		free_lexer(glob->root);
		free_envp(&glob->envp);
		ft_free_id_list(&glob->id_node);
		free(glob);
		exit(EXIT_SUCCESS);
	}
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

int	ft_heredoc_child(t_lexer *node, int *pipe_fd, t_glob *glob, char *full_string)
{
	char *tmp;

	tmp = NULL;
	signal(SIGQUIT, handler_heredoc);
	signal(SIGINT, handler_heredoc);
	while (node && node->type == HEREDOC)
	{
		write(1, "> ", 2);
		tmp = get_next_line(STDIN_FILENO);
		if (tmp && ft_strncmp(node->value[0], tmp, ft_strlen(tmp) - 1) != 0)
		{
			full_string = ft_strjoin2(full_string, tmp);
			if (!full_string)
				return (free(tmp), exit(EXIT_FAILURE), 1);
			free(tmp);
		}
		else if (tmp == NULL || tmp[0] == '\0')
			return (printf("\n"), close(pipe_fd[READ]), close(pipe_fd[WRITE]), free(full_string), free(tmp), ft_heredoc_free(node, glob), exit(0), 1);
		else if (ft_strlen(tmp) > 1 && ft_strncmp(node->value[0], tmp,
				ft_strlen(tmp) - 1) == 0)
		{
			ft_heredoc_init(node, pipe_fd, &full_string, &tmp);
			ft_heredoc_free(node, glob);
			node = node->next;
		}
	}
	exit(EXIT_SUCCESS);
}

int	ft_empty_after_heredoc(t_lexer *node)
{
	t_lexer	*current;

	current = node;
	if (!node)
		return (1);
	while (node)
	{
		if (node->type != HEREDOC && !(node->type >= 6 && node->type <= 9) && node->type != 1)
			return (0);
		node = node->next;
	}
	return (1);
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
	if (node->next)
	{
		close(old_stdin);
		if (pipe(pipe_fd) < 0)
			return (exit(EXIT_FAILURE), 1);
	}
	if (ft_empty_after_heredoc(node) == 1)
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
	char	*full_string;

	full_string = NULL;
	if (!node || node->type != HEREDOC)
		return (0);
	if (pipe(pipe_fd) < 0)
		return (1);
	id = fork();
	if (id < 0)
		return (close(pipe_fd[WRITE]), close(pipe_fd[READ]), 1);
	if (id == 0)
		ft_heredoc_child(node, pipe_fd, glob,full_string);
	else
	{
		old_stdin = dup(STDIN_FILENO);
		if (old_stdin == -1)
			return (close(pipe_fd[WRITE]), close(pipe_fd[READ]), 1);
		ft_heredoc_parent(pipe_fd, id, node, old_stdin);
	}
	return (0);
}
