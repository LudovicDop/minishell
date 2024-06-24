/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_special_redirection.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:30:32 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/18 17:04:38 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	special_carac(t_cmd *cmd)
{
    int fd;
	if (!ft_strncmp(cmd->arg_redirection, ">", 1))
	{
		cmd->arg_redirection++;
		fd = open(cmd->arg_redirection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("open");
		}
		dup2(fd, STDOUT_FILENO);
	}
}
