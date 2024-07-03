/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:02:43 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/03 17:29:07 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redirection_file(t_token *token, char *file_to_created)
{
	int fd;

	if (file_to_created)
	{
		fd = open(file_to_created, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
			perror("open");
		dup2(fd, STDOUT_FILENO);
	}
}

void	ft_red_out(t_token *token)
{
	char	**tmp;
	int	i;
	int	fd;

	i = 0;
	if (!token || token->type != REDIRECT_OUT)
		return ;
	tmp = ft_split(token->value, ' ');
	if (!tmp)
		return ;
	while (tmp[i + 1])
	{
		fd = open(tmp[i], O_CREAT, 0644);
		if (fd < 0)
			perror("open");
		close(fd);
		i++;
	}
	ft_redirection_file(token, tmp[i]);
}
