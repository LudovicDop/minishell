/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:08:25 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/04 15:57:09 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(t_token *node)
{
	char	*tmp;
	int		max;

	tmp = NULL;
	if (!node && node->type != HEREDOC)
		return (1);
	while (1)
	{
		tmp = get_next_line(STDIN_FILENO);
		if (tmp)
		{
			max = ft_strlen(tmp);
			tmp[max - 1] = '\0';
		}
		if (tmp == NULL)
			return (1);
		if (tmp == NULL || ft_strcmp(node->value, tmp) == 0)
		{
			free(tmp);
			break ;
		}
		free(tmp);
	}
	return (0);
}
