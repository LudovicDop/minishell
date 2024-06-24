/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:59:05 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/24 10:58:22 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_envp **envp_list)
{
	t_envp	*current;

	current = *envp_list;
	while (current)
	{
		printf("%s=", current->key);
		printf("%s\n", current->value);
		current = current->next;
	}
	return ;
}
