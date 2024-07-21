/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:17:12 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/21 17:53:26 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_new_key(t_envp **envp, char *key, char *value)
{
	t_envp	*new_node;

	new_node = malloc(sizeof(t_envp));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	if (!new_node->key)
		return ;
	new_node->value = ft_strdup(value);
	if (!new_node)
		return ;
	new_node->next = NULL;
	add_node_to_envp(envp, new_node);
}

void	search_key_and_replace_it(t_envp **envp, char *key, char *value)
{
	t_envp	*envp_t;

	envp_t = *envp;
	while (envp_t)
	{
		if (!ft_strcmp(envp_t->key, key))
		{
			free(envp_t->value);
			envp_t->value = ft_strdup(value);
			return ;
		}
		envp_t = envp_t->next;
	}
	create_new_key(envp, key, value);
	return ;
}

void	init_swap_value(char *tmp_key, char *tmp_value, t_envp *i, t_envp *j)
{
	bool	tmp_hidden_bis;

	tmp_hidden_bis = i->hidden_bis;
	tmp_value = i->value;
	tmp_key = i->key;
	i->hidden_bis = j->hidden_bis;
	i->key = j->key;
	i->value = j->value;
	j->key = tmp_key;
	j->value = tmp_value;
	j->hidden_bis = tmp_hidden_bis;
}

void	sort_list(t_envp **envp)
{
	t_envp	*i;
	t_envp	*j;
	char	*tmp_key;
	char	*tmp_value;

	if (!envp)
		return ;
	i = *envp;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strncmp(i->key, j->key, ft_strlen(i->key)
					+ ft_strlen(j->key)) > 0)
				init_swap_value(tmp_key, tmp_value, i, j);
			j = j->next;
		}
		i = i->next;
	}
	return ;
}

void	print_env_export(t_envp **envp)
{
	t_envp	*tmp;

	if (!envp)
		return ;
	tmp = *envp;
	sort_list(&tmp);
	while (tmp)
	{
		if (tmp->hidden_bis != true)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
