/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_envp_convert.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:50:52 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/22 15:57:27 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_of_envp(t_envp *envp_list)
{
	t_envp	*current;
	int		i;

	i = 0;
	current = envp_list;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

char	**convert_envp(t_envp *envp_list)
{
	char	**envp;
	t_envp	*current;
	int		size_list;
	int		i;

	i = 0;
	current = envp_list;
	size_list = size_of_envp(current) + 1;
	envp = malloc(sizeof(char *) * size_list);
	while (current)
	{
		envp[i] = ft_strjoin(current->key, "=");
		if (!envp[i])
			return (NULL);
		envp[i] = ft_strjoin2(envp[i], current->value);
		if (!envp[i])
			return (NULL);
		current = current->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
