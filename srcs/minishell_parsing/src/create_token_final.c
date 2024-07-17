/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_final.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:37:22 by alphan            #+#    #+#             */
/*   Updated: 2024/07/16 03:16:19 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/create_token_final.h"

void	incr_index(t_token *c, t_index *a)
{
	if (c->type == CMD)
		a->i++;
	else if (c->type == REDIRECT_OUT || c->type == REDIRECT_APPEND)
		a->j++;
	else if (c->type == REDIRECT_IN)
		a->k++;
	else if (c->type == HEREDOC)
		a->l++;
}

void	count_value(t_token *c, t_index *a)
{
	while (c->next && (c->type == CMD || c->type == REDIRECT_OUT || \
		c->type == REDIRECT_APPEND || c->type == REDIRECT_IN || \
		c->type == HEREDOC))
	{
		incr_index(c, a);
		c = c->next;
	}
	if (!c->next && (c->type == CMD || c->type == REDIRECT_OUT || \
		c->type == REDIRECT_APPEND || c->type == REDIRECT_IN || \
		c->type == HEREDOC))
	{
		incr_index(c, a);
		c = c->next;
	}
}

void	create_value(t_lexer **token, t_token **c, t_token_type type, int i)
{
	char	**value;
	int		j;

	j = 0;
	if (i)
	{
		value = ft_calloc(sizeof(char *), i + 1);
		if (!value)
			return ;
		while ((*c)->next && ((*c)->type == CMD || (*c)->type == REDIRECT_OUT \
			|| (*c)->type == REDIRECT_APPEND || (*c)->type == REDIRECT_IN || \
			(*c)->type == HEREDOC))
		{
			if ((*c)->type == type)
				value[j++] = ft_strdup((*c)->value);
			(*c) = (*c)->next;
		}
		if (!(*c)->next && (*c)->type == type)
		{
			value[j++] = ft_strdup((*c)->value);
			(*c) = (*c)->next;
		}
		push_stack2(token, type, value);
	}
}

t_token_type	search_red_type(t_token **c)
{
	t_token_type	type;
	t_token			*t;

	t = *c;
	while (t->next && (t->type == CMD || t->type == REDIRECT_OUT || \
	t->type == REDIRECT_APPEND || t->type == REDIRECT_IN || \
	t->type == HEREDOC))
	{
		if (t->type == REDIRECT_OUT || t->type == REDIRECT_APPEND)
			type = t->type;
		t = t->next;
	}
	if (!t->next && \
		(t->type == REDIRECT_OUT || t->type == REDIRECT_APPEND))
	{
		type = t->type;
		t = t->next;
	}
	return (type);
}

void	create_red_value(t_lexer **t, t_token **c, t_index a)
{
	char			**value;
	t_token_type	type;

	a.i = 0;
	type = search_red_type(c);
	value = ft_calloc(sizeof(char *), a.j + 1);
	if (!value)
		return ;
	while ((*c)->next && ((*c)->type == CMD || (*c)->type == REDIRECT_OUT || \
	(*c)->type == REDIRECT_APPEND || (*c)->type == REDIRECT_IN || \
	(*c)->type == HEREDOC))
	{
		if ((*c)->type == REDIRECT_OUT || (*c)->type == REDIRECT_APPEND)
			value[a.i++] = ft_strdup((*c)->value);
		(*c) = (*c)->next;
	}
	if (!(*c)->next && \
		((*c)->type == REDIRECT_OUT || (*c)->type == REDIRECT_APPEND))
	{
		value[a.i++] = ft_strdup((*c)->value);
		(*c) = (*c)->next;
	}
	push_stack2(t, type, value);
}
