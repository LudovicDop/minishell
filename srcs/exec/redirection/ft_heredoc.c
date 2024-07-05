/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:08:25 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/05 11:34:08 by ldoppler         ###   ########.fr       */
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

int	ft_heredoc(t_token *node, int *pipe_fd, t_token *token)
{
	char	*tmp;
	char	*full_string;
	int		length;
	int		max;

	length = 0;
	tmp = NULL;
	full_string = NULL;
	if (!node && node->type != HEREDOC)
		return (0);
	while (1)
	{
		write(1, "> ", 2);
		tmp = get_next_line(STDIN_FILENO);
		remove_return_line(tmp);
		if (ft_strcmp(node->value, tmp) != 0)
		{
			if (tmp)
			{
				max = ft_strlen(tmp);
				tmp[max] = '\n';
			}
			full_string = ft_strjoin2(full_string, tmp);
		}
		printf("\033[31;1mfull_string : %s\033[m\n", full_string);
		if (tmp == NULL || tmp[0] == '\0')
			return (free(full_string), free(tmp), 1);
		else if (ft_strcmp(node->value, tmp) == 0)
		{
			pipe(pipe_fd);
			length = ft_strlen(full_string);
			write(pipe_fd[WRITE], full_string, length);
			dup2(pipe_fd[READ], STDIN_FILENO);
			close(pipe_fd[READ]);
			close(pipe_fd[WRITE]);
			free(tmp);
			free(full_string);
			break ;
		}
		free(tmp);
	}
	return (0);
}
