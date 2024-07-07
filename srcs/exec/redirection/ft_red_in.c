/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:18:06 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/07 13:34:09 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_red_in(t_lexer *token)
{
	int	fd;

	if (!token || token->type != REDIRECT_IN)
		return (1);
	fprintf(stderr ,"ici : %s\n", token->value[0]);
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