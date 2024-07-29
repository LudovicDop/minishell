/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:44:03 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/29 16:05:19 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_everyone(t_glob *glob)
{
	t_id	*tmp;

	if (!glob || !glob->id_node)
		return ;
	tmp = glob->id_node;
	while (tmp)
	{
		if (waitpid(tmp->id, &g_signal, 0) == -1)
			return ;
		g_signal = WEXITSTATUS(g_signal);
		if (g_signal > 0)
			g_signal = 127;
		tmp = tmp->next;
	}
	return ;
}

void	ft_wait_last_cmd(t_glob *glob)
{
	t_id	*tmp;

	if (!glob || !glob->id_node)
		return ;
	tmp = glob->id_node;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		if (waitpid(tmp->id, &g_signal, 0) == -1)
			return ;
		g_signal = WEXITSTATUS(g_signal);
		if (g_signal > 0)
			g_signal = 127;
		tmp = tmp->next;
	}
	return ;
}

void	handler3(int sig)
{
	g_signal = 130;
	(void)sig;
	printf("\n");
}

void	execute_exec(t_lexer *token, t_envp *envp_list, int *pipe_fd,
		t_glob *glob)
{
	char	*path;
	char	**tmp_envp;

	path = NULL;
	path = test_good_path_for_exec(token->value[0], search_path(envp_list));
	tmp_envp = convert_envp(envp_list);
	if (!path || execve(path, token->value, tmp_envp) < 0)
	{
		free_tab((void **)tmp_envp);
		execute_fail(glob, token, envp_list, pipe_fd);
	}
	exit(EXIT_SUCCESS);
}

void	ft_error_exec(char *error_msg, char *cmd_name)
{
	ft_putstr_fd("nemshell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_msg, 2);
}
