/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:53:12 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/16 15:41:47 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redirection(t_lexer *node, int *pipe_fd, t_glob *glob, t_envp *envp_list)
{
	int	i;

	i = 0;
	if (node->type >= 6 && node->type <= 9)
	{
		if (glob->root == node)
			i = 1;
		ft_red_out(node, i);
		ft_red_append(node, i);
		if (ft_red_in(node))
		{
			dup2(glob->fd_in_old, STDIN_FILENO);
			return (execute_ast(ft_skip_to_next_cmd(node), pipe_fd, envp_list,
					glob));
		}
		ft_heredoc(node, pipe_fd, glob->root, envp_list);
	}
	return (0);
}
