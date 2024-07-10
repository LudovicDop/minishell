/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:08:25 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/10 15:16:52 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_return_line(char *string)
{
	int	i;

	i = 0;
	if (!string)
		return ;
	while (string[i] && string[i] != '\n')
	{
		i++;	
	}
	if (string[i] == '\n')
		string[i] = '\0';
	return ;
}

int	ft_heredoc(t_lexer *node, int *pipe_fd, t_lexer *root, t_envp *envp_list)
{
	int		old_stdin;
	pid_t	id;
	char	*tmp;
	char	*full_string;
	int		max;

	tmp = NULL;
	full_string = NULL;
	pipe(pipe_fd);
	id = fork();
	old_stdin = dup(STDIN_FILENO);
	if (!node || node->type != HEREDOC)
		return (0);
	if (id == 0)
	{
		signal(SIGQUIT, handler_heredoc);
		signal(SIGINT, handler_heredoc);
		while (node && node->type == HEREDOC)
		{
			write(1, "> ", 2);
			tmp = get_next_line(STDIN_FILENO);
			remove_return_line(tmp);
			if (tmp && ft_strcmp(node->value[0], tmp) != 0)
			{
				max = ft_strlen(tmp);
				tmp[max] = '\n';
				full_string = ft_strjoin2(full_string, tmp);
			}
			if (tmp == NULL || tmp[0] == '\0')
			{
				printf("\n");
				return (free(full_string), free(tmp), exit(0), 1);
			}
			else if (ft_strcmp(node->value[0], tmp) == 0)
			{
				if (!node->next || node->next->type != HEREDOC)
				{
					close(pipe_fd[READ]);
					write(pipe_fd[WRITE], full_string, ft_strlen(full_string));
					close(pipe_fd[WRITE]);
					free(full_string);
					free(tmp);
					exit(EXIT_SUCCESS);
					break;
				}
				else
				{
					free(tmp);
					free(full_string);
					tmp = NULL;
					full_string = NULL;
				} 
				node = node->next;
			}
		}
	}
	else
	{
		close(pipe_fd[WRITE]);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		waitpid(id, 0, 0);
		dup2(pipe_fd[READ], STDIN_FILENO);
		close(pipe_fd[READ]);
		if (node->next)
			pipe(pipe_fd);
		if (!node->next)
			dup2(old_stdin, STDIN_FILENO);
	}
	return (0);
}
