/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:08:25 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/04 16:46:10 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void handler(int signal)
// {
//     if (signal == SIGINT)
//     {
//         g_interrupt = 1;
//         // Write a null character to stdin
//         write(STDIN_FILENO, "\0", 1);
//     }
//     else if (signal == SIGQUIT)
//     {
//         // Write a null character to stdin
//         write(STDIN_FILENO, "\0", 1);
//     }
// }
int	ft_heredoc(t_token *node)
{
	char	*tmp;
	int		max;

	tmp = NULL;
	if (!node && node->type != HEREDOC)
		return (1);
	while (1)
	{
		reset_signal();
		init_signal(2);
		tmp = readline(">");
		// if (tmp)
		// {
		// 	max = ft_strlen(tmp);
		// 	tmp[max] = '\0';
		// }
		printf("=> %s", tmp);
		if (tmp == NULL || tmp[0] == '\0')
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
