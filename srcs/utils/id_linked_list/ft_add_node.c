/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 10:27:27 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/16 15:02:26 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_lst_id_node(t_id **id_node, pid_t new_id_value)
{
	t_id	*new_node;
	t_id	*current;

	current = *id_node;
	if (!new_id_value)
		return ;
	if (!current)
	{
		*id_node = ft_calloc(1, sizeof(t_id));
		if (!*id_node)
			return ;
		(*id_node)->id = new_id_value;
		(*id_node)->next = NULL;
		return ;
	}
	while (current->next)
	{
		current = current->next;
	}
	new_node = ft_calloc(1, sizeof(t_id));
	if (!new_node)
		return ;
	current->next = new_node;
	new_node->id = new_id_value;
	new_node->next = NULL;
}
