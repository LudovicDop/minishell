/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:46:51 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/30 00:48:49 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_signal_exit(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		g_signal = 130;
	}
}

void	handler2(int sig)
{
	int	pipe_fd[2];

	if (sig == SIGINT)
	{
		if (pipe(pipe_fd) < 0)
			return ;
		close(pipe_fd[WRITE]);
		dup2(pipe_fd[READ], STDIN_FILENO);
		close(pipe_fd[READ]);
		return ;
	}
}

void	handler_heredoc(int sig)
{
	rl_catch_signals = 1;
	if (sig == SIGINT)
		ft_heredoc_init_exit();
	if (sig == SIGQUIT)
		ft_heredoc_init_exit();
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("^C\n");
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		rl_redisplay();
}

void	init_signal(int choice)
{
	struct sigaction	action;

	if (choice == 1)
	{
		action.sa_handler = &handler;
		sigemptyset(&action.sa_mask);
		action.sa_flags = 0;
		sigaction(SIGINT, &action, NULL);
		sigaction(SIGQUIT, &action, NULL);
	}
	else if (choice == 2)
	{
		action.sa_handler = &handler_heredoc;
		sigemptyset(&action.sa_mask);
		action.sa_flags = 0;
		sigaction(SIGINT, &action, NULL);
	}
}
