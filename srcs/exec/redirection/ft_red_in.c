/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:18:06 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/17 17:10:28 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_red_in_bis(t_lexer *token, int i)
{
	int	fd;

	fd = open(token->value[i], O_RDONLY);
	if (fd < 0)
	{
		ft_error_exec("no such file or directory\n", token->value[i]);
		return (1);
	}
	if (!token->next || token->next->type != CMD)
	{
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		perror("dup2");
	close(fd);
	return (0);
}

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
			ft_error_exec("no such file or directory\n", token->value[i]);
			return (1);
		}
		close(fd);
		i++;
	}
	if (ft_red_in_bis(token, i))
		return (1);
	return (0);
}
