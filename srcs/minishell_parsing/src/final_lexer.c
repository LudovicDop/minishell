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

void	final_lexer(t_token *t, t_lexer **token)
{
	t_token	*c;
	char	**value;

	c = t;
	*token = NULL;
	while (c)
	{
		if (c->next && (c->type == CMD || c->type == REDIRECT_OUT || \
			c->type == REDIRECT_APPEND || c->type == REDIRECT_IN))
			create_token(&c, token);
		else
		{
			value = ft_calloc(sizeof(char *), 2);
			if (!value)
				return ;
			value[0] = ft_strdup(c->value);
			push_stack2(token, c->type, value);
			c = c->next;
		}
	}
}
