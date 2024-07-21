/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:05:55 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/21 17:55:26 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*test_good_path_for_exec(char *exec_name, char *path)
{
	int		i;
	char	*tmp;
	char	*tmp_bis;
	char	**split_path;

	if (access(exec_name, F_OK) == 0)
		return (exec_name);
	if (!path)
		return (NULL);
	split_path = ft_split(path, ':');
	i = 0;
	while (split_path[i])
	{
		tmp_bis = ft_strjoin(split_path[i], "/");
		tmp = ft_strjoin(tmp_bis, exec_name);
		if (access(tmp, F_OK) == 0)
			return (free(tmp_bis), free_tab((void **)split_path), tmp);
		free(tmp_bis);
		free(tmp);
		i++;
	}
	free_tab((void **)split_path);
	return (NULL);
}

char	*search_path(t_envp *envp_list)
{
	t_envp	*current;

	current = envp_list;
	while (current)
	{
		if (!ft_strncmp(current->key, "PATH", sizeof(char) * 5))
		{
			return (current->value);
		}
		current = current->next;
	}
	return (NULL);
}

void	add_node_to_envp(t_envp **list, t_envp *new_node)
{
	t_envp	*current;

	if (*list == NULL)
	{
		*list = new_node;
		return ;
	}
	current = *list;
	while (current->next)
	{
		current = current->next;
	}
	current->next = new_node;
}

void	init_envp(t_envp **envp_list, char **envp)
{
	int		i;
	t_envp	*current;
	t_envp	*new_node;

	i = 0;
	current = *envp_list;
	while (envp[i])
	{
		new_node = ft_calloc(1, sizeof(t_envp));
		if (!new_node)
		{
			free_tab((void **)envp_list);
			return ;
		}
		new_node->value = ft_strdup(ft_strchr2(envp[i], '='));
		new_node->key = ft_strchr_reverse(envp[i], '=');
		new_node->next = NULL;
		add_node_to_envp(envp_list, new_node);
		i++;
	}
}
