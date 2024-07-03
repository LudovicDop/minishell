/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:24:32 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/03 17:29:29 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_redirection_file(t_token *token, char *file_to_created)
{
	int fd;

	if (file_to_created)
	{
		fd = open(file_to_created, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd < 0)
			perror("open");
		dup2(fd, STDOUT_FILENO);
	}
}

void	ft_red_append(t_token *token)
{
	char	**tmp;
	int	i;
	int	fd;

	i = 0;
	if (!token || token->type != REDIRECT_APPEND)
		return ;
	printf("start append\n");
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