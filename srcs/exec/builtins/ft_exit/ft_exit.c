/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:51:18 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/11 17:25:40 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_lexer *token, char *val)
{
	unsigned int	convert_val;

	convert_val = 0;
	if (!val)
	{
		exit(EXIT_SUCCESS);
	}
	convert_val = ft_atoi(val);
	convert_val %= 256;
	exit(convert_val);
}
