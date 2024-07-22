/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:57:38 by alphan            #+#    #+#             */
/*   Updated: 2024/07/16 14:29:58 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/final_lexer.h"

void	create_token(t_token **c, t_lexer **token)
{
	t_token	*tmp;
	t_index	a;

	tmp = *c;
	a = (t_index){0, 0, 0, 0};
	count_value(*c, &a);
	create_value(token, c, HEREDOC, a.l);
	if (a.k)
		*c = tmp;
	create_value(token, c, REDIRECT_IN, a.k);
	if (a.i)
		*c = tmp;
	create_value(token, c, CMD, a.i);
	if (a.j)
	{
		*c = tmp;
		create_red_value(token, c, a);
		// if ((*c)->type == CMD && (*c)->next)
		// 	*c = (*c)->next;
	}
}

void	final_lexer(t_token *t, t_lexer **token)
{
	t_token	*c;
	char	**value;

	c = t;
	*token = NULL;
	while (c)
	{
		if ((c->type == CMD || c->type == REDIRECT_OUT || \
			c->type == REDIRECT_APPEND || c->type == REDIRECT_IN))
			create_token(&c, token);
		else if (c->type != SPACE)
		{
			value = ft_calloc(sizeof(char *), 2);
			if (!value)
				return ;
			value[0] = ft_strdup(c->value);
			push_stack2(token, c->type, value);
			c = c->next;
		}
		else
			c = c->next;
	}
}
