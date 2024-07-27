/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:17 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/27 15:39:04 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_parsing/includes/parser.h"
#include "minishell.h"

void	execute_exec(t_lexer *token, t_envp *envp_list, int *pipe_fd,
		t_glob *glob)
{
	char	*path;
	char	**tmp_envp;

	path = NULL;
	path = test_good_path_for_exec(token->value[0], search_path(envp_list));
	tmp_envp = convert_envp(envp_list);
	fprintf(stderr, "path : %s && token->value : %s\n", path, token->value[0]);
	if (!path || execve(path, token->value, tmp_envp) < 0)
	{
		perror("execve");
		fprintf(stderr, "there is bug\n");
		free_tab((void **)tmp_envp);
		execute_fail(glob, token, envp_list, pipe_fd);
	}
	exit(EXIT_SUCCESS);
}

void	execute_child(t_glob *glob, t_lexer *token, t_envp *envp_list,
		int *pipe_fd)
{
	signal(SIGINT, handler3);
	if (pipe_fd[0])
		close(pipe_fd[READ]);
	if (token->next && token->next->type == PIPE)
	{
		if (dup2(pipe_fd[WRITE], STDOUT_FILENO) == -1)
			return (execute_fail_builtins(glob, envp_list, pipe_fd));
		close(pipe_fd[WRITE]);
	}
	else if (token->next && (token->next->type >= 7 && token->next->type <= 8))
	{
		ft_redirection(token->next, pipe_fd, glob, envp_list);
	}
	if (search_builtins_token(token, &envp_list, glob, pipe_fd))
	{
		return (execute_fail_builtins(glob, envp_list, pipe_fd), exit(0));
	}
	else
		execute_exec(token, envp_list, pipe_fd, glob);
}

int	execute_command(t_lexer **token, int *pipe_fd, t_envp *envp_list,
		t_glob *glob)
{
	pid_t	id;

	if ((*token)->type != CMD)
		return (-1);
	signal(SIGINT, handler3);
	signal(SIGQUIT, handler_heredoc);
	id = fork();
	if (id < 0)
		return (1);
	if (id == 0)
		execute_child(glob, *token, envp_list, pipe_fd);
	else if (id > 0)
	{
		ft_add_lst_id_node(&(glob->id_node), id);
		if (ft_is_it_pipe(glob->root) && pipe_fd[1])
			close(pipe_fd[WRITE]); 
		if ((*token)->next && ((*token)->next->type == 6 || (*token)->next->type == 9))
			(*token) = (*token)->next;
		return (0);
	}
	else
		perror("fork");
	return (0);
}

int	execute_pipeline(t_lexer *node, int *pipe_fd, t_envp *envp_list,
		t_glob *glob)
{
	int	fd_in;

	if (node->type != PIPE)
		return (-1);
	fd_in = pipe_fd[READ];
	if (pipe(pipe_fd) < 0)
		return (1);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (close(pipe_fd[READ]), close(pipe_fd[WRITE]), 1);
	if (fd_in)
		close(fd_in);
	execute_ast(node->next, pipe_fd, &envp_list, glob);
	return (0);
}

int	execute_and(t_lexer *node, t_glob *glob, int *pipe_fd, t_envp **envp_list)
{
	if (node && node->type == 12)
	{
			ft_wait_everyone(glob);
			if (g_signal == 0)
			{
				if (dup2(glob->fd_out_old, STDOUT_FILENO) == -1)
					return (1);
				if (dup2(glob->fd_in_old, STDIN_FILENO) == -1)
					return (1);
				execute_ast(node->next, pipe_fd, envp_list, glob);
				return (1);
			}
			else if (g_signal > 0)
			{
				if (dup2(glob->fd_out_old, STDOUT_FILENO) == -1)
					return (1);
				if (dup2(glob->fd_in_old, STDIN_FILENO) == -1)
					return (1);
				return (1);
			}
	}
	return (0);
}

int	execute_ast(t_lexer *node, int pipe_fd[2], t_envp **envp_list, t_glob *glob)
{
	if (ft_end_cmd(node, glob, pipe_fd))
		return (1);
	if (ft_first_node_init(node, glob, pipe_fd))
		return (1);
	if (execute_and(node, glob, pipe_fd, envp_list))
		return (1);
	if (node->type == PIPE)
		return (execute_pipeline(node, pipe_fd, *envp_list, glob));
	if ((node->type == 6 || node->type == 9))
	{
		if (ft_redirection(node, pipe_fd, glob, *envp_list))
			return (0);
	}
	if (ft_single_cmd(node, glob, pipe_fd, envp_list))
		return (1);
	else if (node->type == CMD)
	{
		fprintf(stderr, "\033[31;1mExecute CMD (cmd : %s) --> normal_cmd\033[m\n", node->value[0]);
		execute_command(&node, pipe_fd, *envp_list, glob);
		if (dup2(glob->fd_in_old, STDIN_FILENO) == -1)
			return (1);
	}
	execute_ast(node->next, pipe_fd, envp_list, glob);
	return (0);
}
