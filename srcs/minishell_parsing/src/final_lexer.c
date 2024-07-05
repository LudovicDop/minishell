/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:57:38 by alphan            #+#    #+#             */
/*   Updated: 2024/07/04 16:40:57 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/final_lexer.h"

void	push_stack2(t_lexer **token, t_token_type t, char **value, int j)
{
	t_lexer				*element;
	t_lexer				*tmp;
	static const int	a[] = {9, 9, 9, 9, 8, 8, 2, 2, 2, 3, 1, 0, 0, 9, 9, 9};
	static int			b;

	(void)j;
	element = ft_calloc(sizeof(t_token), 1);
	if (!element)
		return ;
	*element = (t_lexer){t, value, b++, a[t], NULL};
	tmp = *token;
	if (!tmp)
	{
		*token = element;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = element;
}

void	count_value(t_token *current, t_index *a)
{
	while (current->next && (current->type == CMD || \
		current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND))
	{
		if (current->type == CMD)
			a->i++;
		if (current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND)
			a->j++;
		current = current->next;
	}
	if (!current->next && (current->type == CMD || \
		current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND))
	{
		if (current->type == CMD)
			a->i++;
		if (current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND)
			a->j++;
		current = current->next;
	}
}

void	create_cmd_value(t_lexer **token, t_token **current, t_index a)
{
	char	**value;

	if (a.i)
	{
		a.k = 0;
		value = ft_calloc(sizeof(char *), a.i + 1);
		if (!value)
			return ;
		while ((*current)->next && ((*current)->type == CMD || (*current)->type \
	== REDIRECT_OUT || (*current)->type == REDIRECT_APPEND))
		{
			if ((*current)->type == CMD)
				value[a.k++] = ft_strdup((*current)->value);
			(*current) = (*current)->next;
		}
		if (!(*current)->next && (*current)->type == CMD)
		{
			value[a.k++] = ft_strdup((*current)->value);
			(*current) = (*current)->next;
		}
		push_stack2(token, CMD, value, a.i);
	}
}

void	create_red_value(t_lexer **t, t_token **cur, t_token *tmp, t_index a)
{
	char	**value;

	a.k = 0;
	value = ft_calloc(sizeof(char *), a.j + 1);
	if (!value)
		return ;
	while ((*cur)->next && ((*cur)->type == CMD || \
		(*cur)->type == REDIRECT_OUT || (*cur)->type == REDIRECT_APPEND))
	{
		if ((*cur)->type == REDIRECT_OUT || (*cur)->type == REDIRECT_APPEND)
		{
			value[a.k++] = ft_strdup((*cur)->value);
			tmp->type = (*cur)->type;
		}
		(*cur) = (*cur)->next;
	}
	if (!(*cur)->next && \
		((*cur)->type == REDIRECT_OUT || (*cur)->type == REDIRECT_APPEND))
	{
		value[a.k++] = ft_strdup((*cur)->value);
		tmp->type = (*cur)->type;
		(*cur) = (*cur)->next;
	}
	push_stack2(t, tmp->type, value, a.j);
}

void	final_lexer(t_token *t, t_lexer **token)
{
	t_token	*current;
	t_token	*tmp;
	t_index	a;
	char	**value;

	current = t;
	*token = NULL;
	while (current)
	{
		a = (t_index){0, 0, 0};
		if (current->next && (current->type == CMD || \
			current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND))
		{
			tmp = current;
			count_value(current, &a);
			create_cmd_value(token, &current, a);
			if (a.j)
			{
				current = tmp;
				create_red_value(token, &current, tmp, a);
			}
		}
		else
		{
			a.k = 0;
			value = ft_calloc(sizeof(char *), 2);
			if (!value)
				return ;
			value[a.k] = ft_strdup(current->value);
			push_stack2(token, current->type, value, 1);
			current = current->next;
		}
	}
}
