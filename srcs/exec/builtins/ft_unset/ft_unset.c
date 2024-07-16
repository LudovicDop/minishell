/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:28:25 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/16 19:29:34 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_envp **envp, char *key_to_remove)
{
	t_envp	*i;
	t_envp	*tmp;

	i = *envp;
	if (!key_to_remove)
		return ;
	while (i)
	{
		if (!ft_strcmp(i->key, key_to_remove))
		{
			tmp->next = i->next;
			return (free(i->key), free(i->value), free(i));
		}
		tmp = i;
		i = i->next;
	}
	return ;
}
