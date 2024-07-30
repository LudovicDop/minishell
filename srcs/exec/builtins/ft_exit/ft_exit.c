/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:51:18 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/30 19:32:17 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_num(char *string)
{
	int	i;

	i = 0;
	if (!string)
		return (true);
	while (string[i])
	{
		if (!(string[i] >= 48 && string[i] <= 57))
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit_bis(t_lexer *token, t_envp **envp_list, t_glob *glob,
		int *pipe_fd)
{
	if (token->value[1] && token->value[2])
	{
		ft_putstr_fd("nemshell: exit: too many arguments\n", 2);
		exit_free(glob, *envp_list, pipe_fd);
		exit(1);
	}
	else if (ft_is_num(token->value[1]) == false)
	{
		ft_putstr_fd("nemshell: exit: numeric argument required\n", 2);
		exit_free(glob, *envp_list, pipe_fd);
		exit(2);
	}
}

void	exit_free(t_glob *glob, t_envp *envp_list, int *pipe_fd)
{
	free(glob->prompt);
	free_lexer(glob->root);
	free_envp(&envp_list);
	ft_free_id_list(&glob->id_node);
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
	if (glob->fd_in_old)
		close(glob->fd_in_old);
	free(glob);
}

void	ft_exit(char *val, t_glob *glob, int *pipe_fd)
{
	unsigned int	convert_val;

	convert_val = 0;
	if (!val)
	{
		printf("exit\n");
		execute_fail_builtins(glob, glob->envp, pipe_fd);
		exit(EXIT_SUCCESS);
	}
	convert_val = ft_atoi(val);
	convert_val %= 256;
	printf("exit\n");
	exit_free(glob, glob->envp, pipe_fd);
	exit(convert_val);
}
