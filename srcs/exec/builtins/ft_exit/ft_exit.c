/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:51:18 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/21 17:21:25 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_lexer *token, char *val, t_glob *glob, int *pipe_fd)
{
	unsigned int	convert_val;

	convert_val = 0;
	if (!val)
	{
		printf("exit\n");
		execute_fail_builtins(glob, token, glob->envp, pipe_fd);
		exit(EXIT_SUCCESS);
	}
	convert_val = ft_atoi(val);
	convert_val %= 256;
	printf("exit\n");
	execute_fail_builtins(glob, token, glob->envp, pipe_fd);
	exit(convert_val);
}
