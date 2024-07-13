/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:18:06 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/13 16:33:19 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_red_in(t_lexer *token)
{
	int	i;
	int	fd;

	i = 0;
	if (!token || token->type != REDIRECT_IN)
		return (0);
	while (token->value[i + 1])
	{
		fd = open(token->value[i], O_RDONLY);
		if (fd < 0)
		{
			perror("open");
			return (1);
		}
		close(fd);
		i++;
	}
	fd = open(token->value[i], O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		perror("dup2");
	close(fd);
	if (!token->next)
		return (1);
	return (0);
}
