/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:28:25 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/17 17:12:26 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_envp **envp, char *key_to_remove)
{
	t_envp	*current;
	t_envp	*tmp;

	if (!envp || !*envp || !key_to_remove)
		return ;
	current = *envp;
	if (!ft_strcmp(current->key, key_to_remove))
	{
		*envp = current->next;
		return (free(current->key), free(current->value), free(current));
	}
	while (current && current->next)
	{
		if (!ft_strcmp(current->next->key, key_to_remove))
		{
			tmp = current->next;
			current->next = tmp->next;
			return (free(tmp->key), free(tmp->value), free(tmp));
		}
		current = current->next;
	}
}
