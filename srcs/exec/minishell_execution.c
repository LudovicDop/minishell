/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:17 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/14 14:20:37 by ludovicdopp      ###   ########.fr       */
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

// void    wait_everyone(t_cmd *cmd_list, int nbre_cmd)
// {
//     int i;

//     i = 0;
//     while (i < nbre_cmd)
//     {
//         waitpid(cmd_list->tab_ref->process_id[i], 0, 0);
//         i++;
//     }
//     wait(NULL);
// }


void    ft_null(int sig)
{
    (void)sig;
    return ;
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
        if (search_builtins_token(token, envp_list))
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
                exit(EXIT_FAILURE);
            }
        }
    }
    else if (id > 0)
    {
        // waitpid(id, 0, 0);
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
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    // id = fork();
    // if (id < 0)
    //     return (-1);
    // if (id == 0)
    // {
	    signal(SIGINT, handler_heredoc);
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
        // execute_ast(node->next, pipe_fd ,envp_list, root);
        // exit(EXIT_FAILURE);
    // }
    // else
    // {
        // close(fd_in);
        // close(pipe_fd[READ]);
        // close(pipe_fd[WRITE]);
        // waitpid(id, &status, 0);
        execute_ast(node->next, pipe_fd ,envp_list, glob);
        // wait(NULL);
    // }
    return (0);
}

int ft_redirection(t_lexer *node, int *pipe_fd, t_glob *glob, t_envp *envp_list)
{
    static int fd_in_old;
    int i = 0;

    fd_in_old = dup(STDIN_FILENO);
    if (fd_in_old < 0)
        return (1);
	if	(node->type >= 6 && node->type <= 9)
    {
        if (glob->root == node)
            i = 1;
        ft_red_out(node, i);
        ft_red_append(node);
        if (ft_red_in(node))
        {
            dup2(fd_in_old, STDIN_FILENO);
            if (node->next && node->next->type == CMD)
            {
                return (execute_ast(node->next->next, pipe_fd, envp_list, glob));
            }
        }
        ft_heredoc(node, pipe_fd, glob->root, envp_list);
    }
	return (0);
}

int execute_ast(t_lexer *node, int pipe_fd[2], t_envp *envp_list, t_glob *glob)
{
    static int fd_in_old;

    if (!node || node->type == 1)
    {
        wait(NULL);
        if (how_many_cmd(glob->root) <= 1)
            return (1);
        return (close(pipe_fd[READ]), close(pipe_fd[WRITE]), 1);
    }
    if (glob->root == node)
    {
        fd_in_old = dup(STDIN_FILENO);
        if (fd_in_old == -1)
            return (1);
        if (how_many_cmd(glob->root) > 1)
        {
            if (pipe(pipe_fd) < 0)
                return (1);
        }
    }
    if (node->type == PIPE)
    {
        return (execute_pipeline(node, pipe_fd,envp_list, glob));
    }
    if (glob->root == node && (node->type >= 6 && node->type <= 9))
	{
        if (ft_redirection(node, pipe_fd, glob, envp_list))
            return (0);
	}
    if (how_many_cmd(glob->root) == 1 && glob->root == node && !node->next)
    {
        if (!search_builtins_token(glob->root, envp_list))
            execute_command(node, pipe_fd, envp_list, glob);
        dup2(fd_in_old, STDIN_FILENO);
    }
    else if (node->type == CMD)
    {
        execute_command(node, pipe_fd, envp_list, glob);
        dup2(fd_in_old, STDIN_FILENO);
    }
    execute_ast(node->next, pipe_fd ,envp_list, glob);
    return (0);
}
