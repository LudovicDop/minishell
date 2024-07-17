/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 09:30:44 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/17 17:32:14 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(t_envp **envp, char *key)
{
	t_envp	*envp_tmp;

	envp_tmp = *envp;
	while (envp_tmp)
	{
		if (!ft_strcmp(envp_tmp->key, key))
		{
			return (envp_tmp->value);
		}
		envp_tmp = envp_tmp->next;
	}
	return (NULL);
}

char	*pwd_until_slash(char *pwd)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!pwd)
		return (NULL);
	while (pwd[j] && pwd[j] != '/')
		j++;
	ret = malloc(sizeof(char) * j + 2);
	while (pwd[i])
	{
		ret[i] = pwd[i];
		if (pwd[i] == '/')
		{
			i++;
			ret[i] = '\0';
			return (ret);
		}
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

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

int	ft_chdir(char *path)
{
	if (chdir(path) < 0)
	{
		g_signal = 1;
		return (ft_error_exec("No such file or directory\n", path), 0);
	}
	g_signal = 0;
	return (1);
}
