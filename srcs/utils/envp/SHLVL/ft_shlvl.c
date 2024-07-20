/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <alphan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:27:01 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/20 16:35:32 by alphan           ###   ########.fr       */
/*   Updated: 2024/07/20 15:12:50 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*search_envp_key(t_envp **envp, char *key)
{
	t_envp	*i;

	i = *envp;
	while (i)
	{
		if (!ft_strcmp(i->key, key))
			return (i);
		i = i->next;
	}
	return (NULL);
}

void	increment_shlvl(t_envp **envp)
{
	t_envp	*node;
	int		shlvl;

	node = search_envp_key(envp, "SHLVL");
	if (node)
	{
		shlvl = ft_atoi(node->value);
		shlvl++;
		free(node->value);
		node->value = ft_itoa(shlvl);
	}
	else
	{
		search_key_and_replace_it(envp, "SHLVL", "1");
	}
	if (!search_value_envp(envp, "_"))
	{
		ft_export(envp, "_=/usr/bin/env");
	}
}
