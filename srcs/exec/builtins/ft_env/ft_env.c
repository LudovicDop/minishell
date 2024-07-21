/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:59:05 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/21 19:12:42 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_envp **envp_list)
{
	t_envp	*current;

	current = *envp_list;
	while (current)
	{
		if (current->hidden_bis != true && current->hidden != true)
		{
			printf("%s=", current->key);
			printf("%s\n", current->value);
		}
		current = current->next;
	}
	g_signal = 0;
	return ;
}
