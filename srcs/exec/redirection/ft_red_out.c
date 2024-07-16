/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:02:43 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/16 15:45:48 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redirection_file(t_lexer *token, char *file_to_created,
		bool is_cmd)
{
	int	fd;

	if (file_to_created)
	{
		fd = open(file_to_created, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			perror("open");
		if (is_cmd == 0)
			dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	ft_red_out(t_lexer *token, bool is_cmd)
{
	int	i;
	int	fd;

	i = 0;
	if (!token || token->type != REDIRECT_OUT)
		return ;
	while (token->value[i + 1])
	{
		fd = open(token->value[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			perror("open");
		close(fd);
		i++;
	}
	ft_redirection_file(token, token->value[i], is_cmd);
}
