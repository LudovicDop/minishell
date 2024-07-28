/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:44:03 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/28 13:55:04 by ldoppler         ###   ########.fr       */
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
		fprintf(stderr, "\033[92;1msignal before : %d\033[m\n", g_signal);
		if (waitpid(tmp->id, &g_signal, 0) == -1)
			return ;
		g_signal = WEXITSTATUS(g_signal);
		if (g_signal > 0)
			g_signal = 127;
		fprintf(stderr, "\033[92;1msignal received : %d\033[m\n", g_signal);
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
		fprintf(stderr, "\033[31;1msignal before : %d (process : %d)\033[m\n", g_signal, tmp->id);
		if (waitpid(tmp->id, &g_signal, 0) == -1)
			return ;
		g_signal = WEXITSTATUS(g_signal);
		if (g_signal > 0)
			g_signal = 127;
		fprintf(stderr, "\033[31;1msignal received : %d (process : %d)\033[m\n", g_signal, tmp->id);
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
