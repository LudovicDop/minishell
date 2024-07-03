/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:18:06 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/03 18:26:50 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_red_in(t_token *token)
{
	int	fd;

	if (!token || token->type != REDIRECT_IN)
		return (1);
	fd = open(token->value, O_RDONLY, 0644);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	return (0);
}