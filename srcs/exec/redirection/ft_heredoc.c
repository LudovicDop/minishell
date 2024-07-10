/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:08:25 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/10 17:30:20 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	remove_return_line(char *string)
// {
// 	int	i;

// 	i = 0;
// 	if (!string)
// 		return ;
// 	while (string[i] && string[i] != '\n')
// 	{
// 		i++;	
// 	}
// 	if (string[i] == '\n')
// 		string[i] = '\0';
// 	return ;
// }

void	ft_heredoc_init(t_lexer *node, int *pipe_fd, char **full_string, char *tmp)
{
	if (!node->next || node->next->type != HEREDOC)
	{
		close(pipe_fd[READ]);
		write(pipe_fd[WRITE], *full_string, ft_strlen(*full_string));
		close(pipe_fd[WRITE]);
		free(*full_string);
		free(tmp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		free(*full_string);
		free(tmp);
		tmp = NULL;
		*full_string = NULL;
	}
}

int	ft_heredoc_child(t_lexer *node, int *pipe_fd, char *tmp, char *full_string)
{
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
			return (printf("\n"), free(full_string), free(tmp), exit(0), 1);
		else if (ft_strncmp(node->value[0], tmp, ft_strlen(tmp) - 1) == 0)
		{
			ft_heredoc_init(node, pipe_fd, &full_string, tmp);
			node = node->next;
		}
	}
	exit(EXIT_SUCCESS);
}

int	ft_heredoc(t_lexer *node, int *pipe_fd, t_lexer *root, t_envp *envp_list)
{
	int		old_stdin;
	pid_t	id;
	char	*tmp;
	char	*full_string;

	tmp = NULL;
	full_string = NULL;
	if (!node || node->type != HEREDOC)
		return (0);
	if (pipe(pipe_fd) < 0)
		return (1);
	id = fork();
	if (id < 0)
		return (close(pipe_fd[WRITE]), close(pipe_fd[READ]), 1);
	old_stdin = dup(STDIN_FILENO);
	if (old_stdin == -1)
		return (close(pipe_fd[WRITE]), close(pipe_fd[READ]), 1);
	if (id == 0)
	{
		ft_heredoc_child(node, pipe_fd, tmp, full_string);
	}
	else
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
			if (pipe(pipe_fd) < 0)
				return (exit(EXIT_FAILURE), 1);
		}
		if (!node->next)
		{
			if (dup2(old_stdin, STDIN_FILENO) == -1)
				return (exit(EXIT_FAILURE), 1);
		}
	}
	return (0);
}
