/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <alphan@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:16:32 by alphan            #+#    #+#             */
/*   Updated: 2024/06/18 11:41:58 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_node	*create_node(t_lexer *token)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->value = token->value;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_lexer	*parse2(t_lexer *token)
{
	t_lexer	*current_token;
	t_lexer	*tmp;

	current_token = token;
	tmp = token;
	while (current_token)
	{
		if (tmp->priority > current_token->priority)
			tmp = current_token;
		current_token = current_token->next;
	}
	return (tmp);
}

t_node	*ast(t_lexer *token, t_lexer *start, t_lexer *end)
{
	t_lexer	*current_token;
	t_lexer	*tmp;
	t_node	*root;
	t_node	*current_node;
	t_node	*new_node;

	current_token = start;
	root = NULL;
	current_node = NULL;
	while (current_token && (&current_token != &end))
	{
		tmp = parse2(current_token);
		new_node = create_node(tmp);
		if (!new_node)
			return (NULL);
		if (!root)
			root = new_node;
		else
			current_node = new_node;
		current_node->left = ast(token, token, tmp);
		current_node->right = ast(token, tmp->next, NULL);
		current_token = current_token->next;
	}
	return (root);
}

/*
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
}*/
