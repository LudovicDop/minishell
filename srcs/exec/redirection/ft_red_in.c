/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:18:06 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/15 15:32:56 by ldoppler         ###   ########.fr       */
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
	if (!token->next || (token->next && token->next->type == 1))
	{
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		perror("dup2");
	close(fd);
	return (0);
}
