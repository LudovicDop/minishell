/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 22:45:17 by alphan            #+#    #+#             */
/*   Updated: 2024/06/22 22:45:20 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/check.h"

int	check_quotes(char *input_cmd)
{
	t_index	a;
	char	c;

	a = (t_index){0, 0, 0};
	while (input_cmd[a.i])
	{
		if (input_cmd[a.i] == '\'' || input_cmd[a.i] == '"')
		{
			c = input_cmd[a.i];
			a.j = 1;
			a.i++;
			while (input_cmd[a.i] && input_cmd[a.i] != c)
				a.i++;
			if (input_cmd[a.i] && input_cmd[a.i++] == c)
				a.j = 0;
		}
		else
			a.i++;
	}
	if (a.j == 1)
	{
		ft_printf("syntax error near unexpected token quote\n");
		return (1);
	}
	return (0);
}
