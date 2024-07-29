/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:08:25 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/30 00:09:14 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_heredoc_init_exit(void)
{
	int	pipe_fd_bis[2];

	g_signal = 130;
	if (pipe(pipe_fd_bis) == -1)
		return ;
	close(pipe_fd_bis[WRITE]);
	if (dup2(pipe_fd_bis[READ], STDIN_FILENO) == -1)
	{
		close(pipe_fd_bis[READ]);
		return ;
	}
	close(pipe_fd_bis[READ]);
	printf("\n");
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
		tmp = readline("> ");
		if (tmp && (ft_strncmp(node->value[0], tmp, ft_strlen(tmp)) != 0
				|| ft_strcmp(tmp, "\n") == 0))
			ft_heredoc_stock_string(&tmp, &full_string);
		else if (tmp == NULL)
			return (ft_norm(pipe_fd, tmp, full_string), ft_heredoc_free(node,
					glob, true), exit(0), 1);
		else if (ft_strlen(tmp) > 1 && ft_strncmp(node->value[0], tmp,
				ft_strlen(tmp)) == 0)
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
	if (waitpid(id, 0, 0) < 0)
		return (1);
	if (dup2(pipe_fd[READ], STDIN_FILENO) == -1)
		return (close(pipe_fd[READ]), 1);
	close(pipe_fd[READ]);
	if (ft_empty_after_heredoc(node) == false)
	{
		close(old_stdin);
		if (pipe(pipe_fd) < 0)
			return (1);
	}
	if (ft_empty_after_heredoc(node) == true)
	{
		if (dup2(old_stdin, STDIN_FILENO) == -1)
			return (1);
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
	signal(SIGQUIT, ft_change_signal_exit);
	signal(SIGINT, ft_change_signal_exit);
	if (!ft_is_it_pipe(node))
		if (pipe(pipe_fd) < 0)
			return (1);
	id = fork();
	if (id < 0)
		return (close(pipe_fd[WRITE]), close(pipe_fd[READ]), 1);
	if (id == 0)
		ft_heredoc_child(node, pipe_fd, glob);
	else
	{
		g_signal = 0;
		old_stdin = dup(STDIN_FILENO);
		if (old_stdin == -1)
			return (close(pipe_fd[WRITE]), close(pipe_fd[READ]), 1);
		ft_heredoc_parent(pipe_fd, id, node, old_stdin);
		if (g_signal == 0)
			return (execute_ast(ft_skip_heredoc(node), pipe_fd, &envp_list, glob),
				1);
		else
			return (execute_ast(skip_until_next_symbol(node), pipe_fd, &envp_list, glob), 1);
	}
	return (0);
}
