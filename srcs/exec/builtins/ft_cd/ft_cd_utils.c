/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:30:44 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/01 14:54:19 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_slash(t_pwd **pwd_node)
{
	t_pwd	*current;
	int		i;

	current = *pwd_node;
	if (!current)
		return ;
	i = ft_strlen(current->node);
	if (i > 1 && current->node[i - 1] == '/')
		current->node[i - 1] = '\0';
	return ;
}

char	*search_value_envp(t_envp **envp, char *key)
{
	t_envp	*current;

	current = *envp;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
