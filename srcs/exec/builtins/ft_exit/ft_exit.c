/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:51:18 by ldoppler          #+#    #+#             */
/*   Updated: 2024/06/27 15:10:38 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_token *token, char *val)
{
	unsigned int	convert_val;

	convert_val = 0;
	if (!val)
	{
		// cmd_list->tab_ref->return_val = 0;
		exit(EXIT_SUCCESS);
	}
	convert_val = ft_atoi(val);
	convert_val %= 256;
	// cmd_list->tab_ref->return_val = convert_val;
	exit(convert_val);
}
