/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:08:25 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/08 17:04:45 by ldoppler         ###   ########.fr       */
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

int	ft_heredoc(t_lexer *node, int *pipe_fd, t_lexer *token)
{
	char	*tmp;
	char	*full_string;
	int		max;

	tmp = NULL;
	full_string = NULL;
	signal(SIGQUIT, handler_heredoc);
	if (!node || node->type != HEREDOC)
		return (0);
	fprintf(stderr, "START HEREDOC\n");
	while (node->type == HEREDOC)
	{
		write(1, "> ", 2);
		tmp = get_next_line(STDIN_FILENO);
		remove_return_line(tmp);
		if (tmp && ft_strcmp(node->value[0], tmp) != 0)
		{
			if (tmp)
			{
				max = ft_strlen(tmp);
				tmp[max] = '\n';
			}
			full_string = ft_strjoin2(full_string, tmp);
		}
		if (tmp == NULL || tmp[0] == '\0')
		{
			printf("\n");
			return (free(full_string), free(tmp), 1);
		}
		else if (ft_strcmp(node->value[0], tmp) == 0)
		{
			if (node->next->type != HEREDOC)
			{
				pipe(pipe_fd);
				write(pipe_fd[WRITE], full_string, ft_strlen(full_string));
				dup2(pipe_fd[READ], STDIN_FILENO);
				close(pipe_fd[READ]);
				close(pipe_fd[WRITE]);
				free(tmp);
				free(full_string);
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
	return (0);
}
