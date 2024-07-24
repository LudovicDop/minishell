/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:46:51 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/24 11:27:28 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
	// int	pipe_fd[2];

	if (sig == SIGINT)
	{
		// if (pipe(pipe_fd) < 0)
		// 	return ;
		// close(pipe_fd[WRITE]);
		// dup2(pipe_fd[READ], STDIN_FILENO);
		// close(pipe_fd[READ]);
		// // ft_putstr_fd("^C\n", 2);
		// // ft_putstr_fd("\n", 2);
		// write(2, "\b\b  \b\b", 7);
		// return ;
		ft_heredoc_init_exit(NULL, NULL, NULL);
	}
	if (sig == SIGQUIT)
	{
		// if (pipe(pipe_fd) < 0)
		// 	return ;
		// close(pipe_fd[WRITE]);
		// dup2(pipe_fd[READ], STDIN_FILENO);
		// close(pipe_fd[READ]);
		// // write(2, "\n", 2);
		// write(2, "\b\b  \b\b", 7);
		// return ;
		ft_heredoc_init_exit(NULL, NULL, NULL);
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
		sigaction(SIGQUIT, &action, NULL);
	}
}
