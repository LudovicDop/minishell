/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:17 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/15 15:31:39 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../minishell_parsing/includes/parser.h"

void    ft_error_exec(char *error_msg, char *cmd_name)
{
    ft_putstr_fd("nemshell: ", 2);
    ft_putstr_fd(cmd_name, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(error_msg, 2);
}

int how_many_cmd(t_lexer *token)
{
    int nbre_of_cmd;

    nbre_of_cmd = 0;
    while (token)
    {
        if (token->type == CMD)
            nbre_of_cmd++;
        token = token->next;
    }
    return (nbre_of_cmd);
}

int execute_command(t_lexer *token, int *pipe_fd, t_envp *envp_list, t_glob *glob)
{
    char **tmp_envp;
    char *path;
    int status;
    pid_t id;

    if (token->type != CMD)
        return (-1);
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    id = fork();
    if (id < 0)
        return (-1);
    if (id == 0)
    {
        signal(SIGINT, handler_heredoc);
        if (pipe_fd)
            close(pipe_fd[READ]);
        if (token->next && token->next->type == PIPE)
        {
            dup2(pipe_fd[WRITE], STDOUT_FILENO);
            close(pipe_fd[WRITE]);
        }
        else if (token->next && (token->next->type >= 6 && token->next->type <= 9))
        {
            ft_redirection(token->next, pipe_fd, glob, envp_list);
        }
        if (search_builtins_token(token, envp_list, glob))
        {
            return (exit(EXIT_FAILURE), 0);
        }
        else
        {
            path = test_good_path_for_exec(token->value[0], search_path(envp_list));
            tmp_envp = convert_envp(envp_list);
            if (execve(path, token->value, tmp_envp) < 0)
            {
                ft_error_exec("command not found\n", token->value[0]);
                free_everything(&glob->root, NULL);
                free_tab((void**)tmp_envp);
                free_envp(&envp_list);
                close(pipe_fd[READ]);
                close(pipe_fd[WRITE]);
                close(glob->fd_in_old);
                exit(EXIT_FAILURE);
            }
        }
    }
    else if (id > 0)
    {
        ft_add_lst_id_node(&(glob->id_node), id);
        if (pipe_fd)
            close(pipe_fd[WRITE]);
        if (token->next && (token->next->type >= 6 && token->next->type <= 9))
            token = token->next->next;
        return (0);
    }
    else
        perror("fork");
    return (0);
}


int execute_pipeline(t_lexer *node,int *pipe_fd, t_envp *envp_list, t_glob *glob)
{
    int fd_in;
    int status;
    pid_t id;
    pid_t id2;

    if (node->type != PIPE)
        return (-1);
    fd_in = pipe_fd[READ];
    if (pipe(pipe_fd) < 0)
        return (-1);
    dup2(fd_in, STDIN_FILENO);
    close(fd_in);
    execute_ast(node->next, pipe_fd ,envp_list, glob);
    return (0);
}

int ft_redirection(t_lexer *node, int *pipe_fd, t_glob *glob, t_envp *envp_list)
{
    int i = 0;

	if	(node->type >= 6 && node->type <= 9)
    {
        if (glob->root == node)
            i = 1;
        ft_red_out(node, i);
        ft_red_append(node);
        if (ft_red_in(node))
        {
            dup2(glob->fd_in_old, STDIN_FILENO);
            if (node->next && node->next->type == CMD)
            {
                return (execute_ast(node->next->next, pipe_fd, envp_list, glob));
            }
        }
        ft_heredoc(node, pipe_fd, glob->root, envp_list);
    }
	return (0);
}

void    ft_wait_everyone(t_glob *glob)
{
    t_id *tmp;

    if (!glob || !glob->id_node)
        return ;
    tmp = glob->id_node;
    while (tmp)
    {
        // fprintf(stderr ,"\033[31;1mWaiting for : %d\033[m\n", tmp->id);
        waitpid(tmp->id, 0, 0);
        tmp = tmp->next;
    }
    return ;
}
int execute_ast(t_lexer *node, int pipe_fd[2], t_envp *envp_list, t_glob *glob)
{
    if (ft_end_cmd(node, glob, pipe_fd))
        return (1);
    if (ft_first_node_init(node, glob, pipe_fd))
        return (1);
    if (node->type == PIPE)
        return (execute_pipeline(node, pipe_fd,envp_list, glob));
    if (glob->root == node && (node->type >= 6 && node->type <= 9))
	{
        if (ft_redirection(node, pipe_fd, glob, envp_list))
            return (0);
	}
    if (ft_single_cmd(node, glob, pipe_fd, envp_list))
    {
        return (1);
    }
    else if (node->type == CMD && how_many_cmd(glob->root) > 1)
    {
        execute_command(node, pipe_fd, envp_list, glob);
        dup2(glob->fd_in_old, STDIN_FILENO);
        if (glob->fd_in_old == -1)
            return (1);
    }
    execute_ast(node->next, pipe_fd ,envp_list, glob);
    return (0);
}
