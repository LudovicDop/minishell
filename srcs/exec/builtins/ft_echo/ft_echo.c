/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:09:55 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/01 17:01:47 by ldoppler         ###   ########.fr       */
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

char	*skip_dollar(char *string)
{
	int	i;
	int	j;
	int	lenght;

	j = 0;
	i = 0;
	lenght = ft_strlen(string);
	while (i < lenght)
	{
		if (string[i] != '$')
			string[j] = string[i];
		else if (string[i] == '$')
			j--;
		j++;
		i++;
	}
	string[j] = '\0';
	return (string);
}

char	*ft_check_dollar(char *string, t_envp **envp, t_token *token)
{
	t_envp	*node;

	if (!ft_strcmp(string, "$"))
		return (ft_strdup("$"));
	// if (!ft_strcmp(string, "$?"))
	// 	return (ft_itoa(token->tab_ref->return_val));
	if (string[0] == '$')
	{
		node = search_envp_value(envp, skip_dollar(string));
		if (node)
			return (ft_strdup(node->value));
		else
			return (ft_strdup(""));
	}
	return (ft_strdup(string));
}

void	ft_echo(char *string, bool without_ret, t_envp **envp, t_token *token)
{
	char	*tmp;

	tmp = NULL;
	if (!string && !without_ret)
	{
		printf("\n");
		return ;
	}
	if (!string && without_ret)
	{
		printf("");
		return ;
	}
	if (without_ret)
	{
		tmp = ft_check_dollar(string, envp, token);
		printf("%s", tmp);
	}
	else if (!without_ret)
	{
		tmp = ft_check_dollar(string, envp, token);
		printf("%s\n", tmp);
	}
	if (tmp)
		free(tmp);
}
