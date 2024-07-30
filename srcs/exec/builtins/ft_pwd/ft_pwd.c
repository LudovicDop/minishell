/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:03:33 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/30 17:39:29 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_key_value(t_envp *envp_list, char *key)
{
	t_envp	*current;

	current = envp_list;
	while (current)
	{
		if (!ft_strncmp(current->key, key, sizeof(char) * 5))
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

void	ft_pwd(t_envp *envp_list)
{
	char	*tmp;

	tmp = search_key_value(envp_list, "PWD");
	g_signal = 0;
	if (tmp)
		printf("%s\n", search_key_value(envp_list, "PWD"));
	else
	{
		tmp = getcwd(0, 0);
		if (!tmp)
			return ;
		printf("%s\n", tmp);
		free(tmp);
	}
}
