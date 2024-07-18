/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:51:18 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/18 15:56:11 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_lexer *token, char *val, t_glob *glob)
{
	unsigned int	convert_val;

	convert_val = 0;
	if (!val)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	convert_val = ft_atoi(val);
	convert_val %= 256;
	printf("exit\n");
	free_lexer(glob->root);
	exit(convert_val);
}
