/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:37:53 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/21 22:11:24 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key_envp(const char *s1)
{
	int		i;
	char	*string;
	char	*ret;

	string = (char *)s1;
	i = 0;
	while (string[i] && string[i] != '=')
		i++;
	if (string[i] == '\0')
		return (NULL);
	ret = ft_calloc(i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (string[i] && string[i] != '=')
	{
		ret[i] = string[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*get_value(const char *s1)
{
	return (ft_strchr2(s1, '='));
}

void	search_key_and_increment_it(t_envp **envp, char *key, char *value)
{
	t_envp	*i;

	i = *envp;
	if (!envp)
		return ;
	while (i)
	{
		if (!ft_strcmp(i->key, key))
		{
			i->value = ft_strjoin2(i->value, value);
			return ;
		}
		i = i->next;
	}
	search_key_and_replace_it(envp, key, value);
	return ;
}

int	is_it_incrementation(char *key)
{
	int	lenght;

	lenght = ft_strlen(key);
	if (key[lenght - 1] == '+')
	{
		key[lenght - 1] = '\0';
		return (1);
	}
	return (0);
}

void	ft_export(t_envp **envp_list, char *key_value)
{
	t_envp		*tmp;
	t_export	exp_tmp;

	fprintf(stderr, "value : %s\n", key_value);
	if (!key_value)
		return (print_env_export(envp_list));
	exp_tmp.value = ft_strdup(get_value(key_value));
	if (!exp_tmp.value)
		return ;
	exp_tmp.key = get_key_envp(key_value);
	if (!exp_tmp.key)
	{
		free(exp_tmp.value);
		search_key_and_replace_it(envp_list, key_value, "");
		tmp = search_envp_key(envp_list, key_value);
		tmp->hidden = true;
		return ;
	}
	if (is_it_incrementation(exp_tmp.key))
	{
		search_key_and_increment_it(envp_list, exp_tmp.key, exp_tmp.value);
		return (free(exp_tmp.value), free(exp_tmp.key));
	}
	search_key_and_replace_it(envp_list, exp_tmp.key, exp_tmp.value);
	return (free(exp_tmp.value), free(exp_tmp.key));
}
