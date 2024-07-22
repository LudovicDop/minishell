/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:09:55 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/22 15:53:44 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*search_envp_value(t_envp **envp, char *key)
{
	t_envp	*current;

	current = *envp;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

void	ft_echo(char *string, bool without_ret)
{
	g_signal = 0;
	if (!string && !without_ret)
	{
		printf("\n");
		return ;
	}
	if (!string && without_ret)
		return ;
	if (without_ret)
	{
		printf("%s", string);
	}
	else if (!without_ret)
	{
		printf("%s\n", string);
	}
}
