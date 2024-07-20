/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:46:51 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/20 19:53:54 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handler_heredoc(int sig)
{
	int	pipe_fd[2];

	if (sig == SIGINT)
	{
		if (pipe(pipe_fd) < 0)
			return ;
		close(pipe_fd[WRITE]);
		dup2(pipe_fd[READ], STDIN_FILENO);
		close(pipe_fd[READ]);
		write(1, "\b\b  \b\b", 7);
		write(1, "\n", 2);
		return ;
	}
	if (sig == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 7);
		exit(0);
		return ;
	}
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("^C\n");
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
	}
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
		printf("\033[31;1mSecond signal mode\033[m\n");
		action.sa_handler = &handler_heredoc;
		sigemptyset(&action.sa_mask);
		action.sa_flags = 0;
		sigaction(SIGINT, &action, NULL);
		sigaction(SIGQUIT, &action, NULL);
	}
}
