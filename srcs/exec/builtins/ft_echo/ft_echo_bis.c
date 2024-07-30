/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 20:07:58 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/30 20:09:33 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo_bis2(char *tmp, t_lexer *token, int i)
{
	tmp = ft_echo_merge(&token->value[i]);
	ft_echo(tmp, false);
	free(tmp);
}
