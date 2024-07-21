/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:44:03 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/21 23:46:14 by ldoppler         ###   ########.fr       */
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
