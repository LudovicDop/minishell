/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:55:27 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/23 08:41:56 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc_free(t_lexer *node, t_glob *glob, bool end)
{
	if (!node->next || (node->next && node->next->type != HEREDOC)
		|| end == true)
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

int	ft_empty_after_heredoc(t_lexer *node)
{
	if (!node)
		return (1);
	while (node)
	{
		if (node->type != HEREDOC && !(node->type >= 6 && node->type <= 9)
			&& node->type != 1)
			return (0);
		node = node->next;
	}
	return (1);
}

void	ft_heredoc_signal(void)
{
	signal(SIGINT, handler_heredoc);
	signal(SIGQUIT, handler_heredoc);
}

void	ft_norm(int *pipe_fd, char *tmp, char *full_string)
{
	printf("\n");
	free(tmp);
	free(full_string);
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
}

void	ft_heredoc_stock_string(char **tmp, char **full_string)
{
	*full_string = ft_strjoin2(*full_string, *tmp);
	if (!*full_string)
		return (free(*tmp), exit(EXIT_FAILURE));
	free(*tmp);
}
