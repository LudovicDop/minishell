/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_final.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:37:22 by alphan            #+#    #+#             */
/*   Updated: 2024/07/12 16:13:37 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/create_token_final.h"

void	count_value(t_token *c, t_index *a)
{
	while (c->next && (c->type == CMD || c->type == REDIRECT_OUT || \
		c->type == REDIRECT_APPEND || c->type == REDIRECT_IN))
	{
		if (c->type == CMD)
			a->i++;
		else if (c->type == REDIRECT_OUT || c->type == REDIRECT_APPEND)
			a->j++;
		else if (c->type == REDIRECT_IN)
			a->k++;
		c = c->next;
	}
	if (!c->next && (c->type == CMD || c->type == REDIRECT_OUT || \
		c->type == REDIRECT_APPEND || c->type == REDIRECT_IN))
	{
		if (c->type == CMD)
			a->i++;
		else if (c->type == REDIRECT_OUT || c->type == REDIRECT_APPEND)
			a->j++;
		else if (c->type == REDIRECT_IN)
			a->k++;
		c = c->next;
	}
}

void	create_cmd_value(t_lexer **token, t_token **c, t_index a)
{
	char	**value;

	a.j = 0;
	if (a.i)
	{
		value = ft_calloc(sizeof(char *), a.i + 1);
		if (!value)
			return ;
		while ((*c)->next && ((*c)->type == CMD || (*c)->type == REDIRECT_OUT \
			|| (*c)->type == REDIRECT_APPEND || (*c)->type == REDIRECT_IN))
		{
			if ((*c)->type == CMD)
				value[a.j++] = ft_strdup((*c)->value);
			(*c) = (*c)->next;
		}
		if (!(*c)->next && (*c)->type == CMD)
		{
			value[a.j++] = ft_strdup((*c)->value);
			(*c) = (*c)->next;
		}
		push_stack2(token, CMD, value);
	}
}

void	create_red_in_value(t_lexer **t, t_token **c, t_index a)
{
	char	**value;

	a.i = 0;
	value = ft_calloc(sizeof(char *), a.k + 1);
	if (!value)
		return ;
	while ((*c)->next && ((*c)->type == CMD || (*c)->type == REDIRECT_OUT || \
	(*c)->type == REDIRECT_APPEND || (*c)->type == REDIRECT_IN))
	{
		if ((*c)->type == REDIRECT_IN)
		{
			value[a.i++] = ft_strdup((*c)->value);
		}
		(*c) = (*c)->next;
	}
	if (!(*c)->next && (*c)->type == REDIRECT_IN)
	{
		value[a.i++] = ft_strdup((*c)->value);
		(*c) = (*c)->next;
	}
	push_stack2(t, REDIRECT_IN, value);
}

void	create_red_value(t_lexer **t, t_token **c, t_index a)
{
	char			**value;
	t_token_type	type;

	a.i = 0;
	value = ft_calloc(sizeof(char *), a.j + 1);
	if (!value)
		return ;
	while ((*c)->next && ((*c)->type == CMD || (*c)->type == REDIRECT_OUT || \
	(*c)->type == REDIRECT_APPEND || (*c)->type == REDIRECT_IN))
	{
		if ((*c)->type == REDIRECT_OUT || (*c)->type == REDIRECT_APPEND)
		{
			value[a.i++] = ft_strdup((*c)->value);
			type = (*c)->type;
		}
		(*c) = (*c)->next;
	}
	if (!(*c)->next && \
		((*c)->type == REDIRECT_OUT || (*c)->type == REDIRECT_APPEND))
	{
		value[a.i++] = ft_strdup((*c)->value);
		type = (*c)->type;
		(*c) = (*c)->next;
	}
	push_stack2(t, type, value);
}

void	create_token(t_token **c, t_lexer **token)
{
	t_token	*tmp;
	t_index	a;

	tmp = *c;
	a = (t_index){0, 0, 0};
	count_value(*c, &a);

	if (a.k)
	{
		*c = tmp;
		create_red_in_value(token, c, a);
	}
	if (a.i)
	{
		*c = tmp;
		create_cmd_value(token, c, a);
	}
	if (a.j)
	{
		*c = tmp;
		create_red_value(token, c, a);
	}
}
