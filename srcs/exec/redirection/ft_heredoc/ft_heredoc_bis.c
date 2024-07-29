/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:24:48 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/30 01:39:36 by ldoppler         ###   ########.fr       */
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

int	ft_heredoc_ret(t_lexer *node, int *pipe_fd, t_glob *glob, t_envp *envp_list)
{
	if (g_signal == 0)
		return (execute_ast(ft_skip_heredoc(node), pipe_fd, &envp_list, glob),
			1);
	else
		return (execute_ast(skip_until_next_symbol(node), pipe_fd, \
		&envp_list, glob), 1);
}
