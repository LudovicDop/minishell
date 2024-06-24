/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:03:39 by ldoppler          #+#    #+#             */
/*   Updated: 2024/06/24 10:55:27 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_pwd_node(t_pwd **pwd_lst, t_pwd *node)
{
	t_pwd	*tmp_lst;

	tmp_lst = *pwd_lst;
	if (!(*pwd_lst))
	{
		*pwd_lst = node;
		return ;
	}
	while (tmp_lst->next)
	{
		tmp_lst = tmp_lst->next;
	}
	tmp_lst->next = node;
	node->next = NULL;
	return ;
}

void	init_pwd_w_envp(t_envp **envp, t_pwd **pwd_lst)
{
	t_pwd	*current;
	char	*new_pwd;

	current = *pwd_lst;
	new_pwd = ft_strdup("");
	if (!current)
		return ;
	while (current)
	{
		new_pwd = ft_strjoin2(new_pwd, current->node);
		if (!new_pwd)
			break ;
		current = current->next;
	}
	search_key_and_replace_it(envp, "PWD", new_pwd);
	free(new_pwd);
}

int	nbre_node(t_pwd **pwd_list)
{
	t_pwd	*current;
	int		i;

	i = 0;
	current = *pwd_list;
	if (!current)
		return (0);
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

void	remove_last_node_pwd(t_pwd **pwd_list)
{
	t_pwd	*current;
	t_pwd	*tmp;

	current = *pwd_list;
	tmp = NULL;
	if (!current)
		return ;
	while (current->next)
	{
		tmp = current;
		current = current->next;
	}
	if (tmp)
	{
		remove_slash(&tmp);
		tmp->next = NULL;
	}
	free(current->node);
	free(current);
	current = NULL;
}
