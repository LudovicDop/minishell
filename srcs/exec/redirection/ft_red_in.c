/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:18:06 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/08 15:33:00 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_red_in(t_lexer *token)
{
	int	fd;

	if (!token || token->type != REDIRECT_IN)
		return (1);
	if (token->next && token->next->type == CMD && token->next->value[1])
		return (0);
	fd = open(token->value[0], O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		perror("dup2");
	close(fd);
	return (0);
}