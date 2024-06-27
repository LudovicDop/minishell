/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:16:32 by alphan            #+#    #+#             */
/*   Updated: 2024/06/27 16:16:41 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_node	*create_node(t_token *token)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->value = ft_strdup(token->value);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node	*parse(t_token *token)
{
	t_node	*root;
	t_node	*current_node;
	t_token	*current_token;
	t_node	*new_node;

	root = NULL;
	current_node = NULL;
	current_token = token;
	while (current_token)
	{
		if (current_token->type >= QUOTE && current_token->type <= AND)
		{
			new_node = create_node(current_token);
			if (!new_node)
				return (NULL);
			if (!root)
				root = new_node;
			else
				current_node->right = new_node;
			current_node = new_node;
		}
		else if (current_token->type == CMD)
		{
			new_node = create_node(current_token);
			if (!new_node)
				return (NULL);
			if (!root)
				root = new_node;
			else
				current_node->right = new_node;
			current_node = new_node;
		}
		current_token = current_token->next;
	}
	return (root);
}
