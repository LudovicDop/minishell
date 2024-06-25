/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chek_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 22:45:38 by alphan            #+#    #+#             */
/*   Updated: 2024/06/22 22:45:40 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/check.h"

int	check_op(t_token *token)
{
	while (token)
	{
		if (token->type == SEP)
		{
			ft_printf("syntax error near unexpected token \n");
			return (1);
		}
		if (token->type >= REDIRECT_IN && token->type <= AND)
		{
			token = token->next;
			while (token && token->type == SPACE)
				token = token->next;
			if (token == NULL || \
				(token->type >= REDIRECT_IN && token->type <= SEP))
			{
				ft_printf("syntax error near unexpected token \n");
				return (1);
			}
		}
		token = token->next;
	}
	return (0);
}
