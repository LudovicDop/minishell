/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:08:25 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/09 22:55:29 by ludovicdopp      ###   ########.fr       */
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
	id = fork();

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
					pipe(pipe_fd);
					write(pipe_fd[WRITE], full_string, ft_strlen(full_string));
					old_stdin = dup(STDIN_FILENO);
					dup2(pipe_fd[READ], STDIN_FILENO);
					close(pipe_fd[READ]);
					close(pipe_fd[WRITE]);
					free(tmp);
					free(full_string);
					if (node->next)
						pipe(pipe_fd);
					if (!node->next)
						dup2(old_stdin, STDIN_FILENO);
					exit(0);
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
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		waitpid(id, 0, 0);
	}
	return (0);
}
