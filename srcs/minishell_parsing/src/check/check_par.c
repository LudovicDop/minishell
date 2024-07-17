/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_par.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:44:04 by alphan            #+#    #+#             */
/*   Updated: 2024/07/16 02:08:20 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/check.h"

int	check_close_par(char *input_cmd)
{
	t_index	a;

	a = (t_index){0, 0, 0, 0};
	while (input_cmd[a.i] && input_cmd[a.i] != '(')
	{
		if (input_cmd[a.i] == ')')
		{
			a.k = 1;
			break ;
		}
		a.i++;
	}
	if (a.k)
		return (1);
	return (0);
}

int	check_par(char *input_cmd)
{
	t_index	a;

	a = (t_index){0, 0, 0, 0};
	a.k = check_close_par(input_cmd);
	if (!(a.k))
	{
		while (input_cmd[a.i])
		{
			if (input_cmd[a.i] == '(')
				a.j++;
			if (input_cmd[a.i] == ')')
				a.j--;
			a.i++;
		}
	}
	if (a.j || a.k)
	{
		ft_printf("syntax error near unexpected token par\n");
		return (1);
	}
	return (0);
}

void	check_token_close_par(t_token *token)
{
	while (token && token->type == SPACE)
		token = token->next;
	if (token->type != CLOSE_PAR && \
		(token->type < REDIRECT_IN || token->type > AND))
	{
		ft_printf("syntax error near unexpected par2\n");
		return ;
	}
	return ;
}

int	check_token_par(t_token *token)
{
	while (token)
	{
		// if (token->type == CLOSE_PAR)
		// 	check_token_close_par(token);
		if (token->type == OPEN_PAR)
		{
			token = token->next;
			while (token && (token->type == SPACE || token->type == OPEN_PAR))
				token = token->next;
			if (token->type == CLOSE_PAR || token->type != CMD)
			{
				ft_printf("syntax error near unexpected par3\n");
				return (1);
			}
		}
		token = token->next;
	}
	return (0);
}
