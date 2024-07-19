/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:54:53 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/19 10:57:21 by ldoppler         ###   ########.fr       */
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
		fprintf(stderr, "\033[31;1mcurrent : %s\033[m\n", current->value[0]);
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
		if (g_signal > 0)
			g_signal = 127;
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
