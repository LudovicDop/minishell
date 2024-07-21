/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:54:53 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/21 23:10:56 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*ft_skip_to_next_cmd(t_lexer *node)
{
	t_lexer	*current;

	current = node;
	if (!node)
		return (NULL);
	while (current && current->type != PIPE)
	{
		current = current->next;
	}
	if (current)
	{
		current = current->next;
	}
	return (current);
}

void	ft_wait_everyone(t_glob *glob)
{
	t_id	*tmp;

	if (!glob || !glob->id_node)
		return ;
	tmp = glob->id_node;
	while (tmp)
	{
		waitpid(tmp->id, &g_signal, 0);
		g_signal = WEXITSTATUS(g_signal);
		if (g_signal > 0)
		{
			fprintf(stderr, "\033[31;1msignal : %d\033[m\n", g_signal);
			g_signal = 127;
		}
		tmp = tmp->next;
	}
	return ;
}

void	ft_error_exec(char *error_msg, char *cmd_name)
{
	ft_putstr_fd("nemshell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_msg, 2);
}

void	execute_fail_builtins(t_glob *glob, t_envp *envp_list,
		int *pipe_fd)
{
	free(glob->prompt);
	free_lexer(glob->root);
	free_envp(&envp_list);
	ft_free_id_list(&glob->id_node);
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
	if (glob->fd_in_old)
		close(glob->fd_in_old);
	free(glob);
	exit(0);
}
