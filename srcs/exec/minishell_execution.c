/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:17 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/05 16:34:30 by ldoppler         ###   ########.fr       */
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
        if (token->type == CMD || (token->type >= 6 && token->type  <= 9))
            nbre_of_cmd++;
        token = token->next;
    }
    printf("nbre of cmd : %d\n", nbre_of_cmd);
    return (nbre_of_cmd);
}

// void    execution_pipe(t_cmd *cmd)
// {
//     char    **tmp_arg;
//     char    **tmp_envp;

//     if (cmd->any_redirection)
//     {
//         special_carac(cmd);
//     }
//     if (search_builtins_cmd(cmd))
//         return ;
//     tmp_arg = ft_split(cmd->arg, ' ');
//     cmd->pathname = test_good_path_for_exec(tmp_arg[0], search_path(&cmd));
//     tmp_envp = convert_envp(cmd->envp_ref);
//     if (execve(cmd->pathname, tmp_arg, tmp_envp) < 0)
//     {
//         ft_error_exec("command not found\n", tmp_arg[0]);
//         free_tab((void**)tmp_arg);
//         free_tab((void**)tmp_envp);
//         return ;
//         //need to free everything
//     }
// }

void    wait_everyone(t_cmd *cmd_list, int nbre_cmd)
{
    int i;

    i = 0;
    while (i < nbre_cmd)
    {
        // waitpid(cmd_list->tab_ref->process_id[i], 0, WNOHANG);
        waitpid(cmd_list->tab_ref->process_id[i], 0, 0);
        i++;
    }
    wait(NULL);
}

// void    child_process(int fd_in, int nbre_cmd, t_cmd *cmd_list)
// {
//     close(cmd_list->tab_ref->pipe_fd[0]);
//     dup2(fd_in, STDIN_FILENO);
//     if (cmd_list->next)
//         dup2(cmd_list->tab_ref->pipe_fd[1], STDOUT_FILENO);
//     close(cmd_list->tab_ref->pipe_fd[1]);
//     execution_pipe(cmd_list);
//     // exit(EXIT_SUCCESS);
// }

// void    parent_process(t_cmd *cmd_list, int *fd_in, int i)
// {
//     close(cmd_list->tab_ref->pipe_fd[1]);
//     *fd_in = cmd_list->tab_ref->pipe_fd[0];
// }

// void    execution_main(t_cmd **cmd)
// {
//     t_cmd   *cmd_list;
//     int nbre_cmd;
//     int fd_in;
//     int i;

//     i = 0;
//     fd_in = 0;
//     cmd_list = *cmd;
//     nbre_cmd = how_many_cmd(cmd_list);
//     if (nbre_cmd == 0)
//         return ;
//     cmd_list->tab_ref->process_id = malloc(sizeof(pid_t) * nbre_cmd);
//     if (nbre_cmd == 1)
//     {
//         if (search_builtins_cmd(cmd_list))
//             return ;
//     }
//     while (cmd_list)
//     {
//         pipe(cmd_list->tab_ref->pipe_fd);
//         cmd_list->tab_ref->process_id[i] = fork();
//         if (cmd_list->tab_ref->process_id[i] == 0)
//         {
//             child_process(fd_in, nbre_cmd, cmd_list);
//             free_everything(cmd, NULL);
//             exit(EXIT_SUCCESS);
//         }
//         parent_process(cmd_list, &fd_in, i);
//         cmd_list = cmd_list->next;
//         i++;
//     }
//     close(fd_in);
//     cmd_list = *cmd;
//     wait_everyone(cmd_list, nbre_cmd);
// }

// test_good_path_for_exec(tmp_arg[0], search_path(&cmd))
// tmp_envp = convert_envp(cmd->envp_ref);
int execute_command(t_lexer *token, int *pipe_fd, t_envp *envp_list, t_lexer *root)
{
    // char **tmp_arg;
    char **tmp_envp;
    char *path;
    int status;
    pid_t id;

    if (token->type != CMD)
        return (-1);
    if (token == root)
    {
        printf("\033[31;1mlaunch pipe\033[m\n");
        pipe(pipe_fd);
        printf("\033[36;1mFD 1 : %d && FD 2 : %d (parent process : %d)\033[m\n", pipe_fd[0], pipe_fd[1], getpid());
    }
    id = fork();
    if (id < 0)
        return (-1);
    if (id == 0)
    {
        printf("\033[31;1mClose FD 0 : %d (child process : %d)\033[m\n", pipe_fd[READ], getpid());
        close(pipe_fd[READ]); // ici
        if (token->next && token->next->type == PIPE)
        {
            fprintf(stderr ,"there you go (id : %d) cmd : %s\n", getpid(), token->value[0]);
            dup2(pipe_fd[WRITE], STDOUT_FILENO);
            printf("\033[31;1mClose FD 1 : %d (parent process : %d)\033[m\n", pipe_fd[WRITE], getpid());
            close(pipe_fd[WRITE]);
        }
        else if (token->next && (token->next->type >= 6 && token->next->type <= 8))
        {
            ft_redirection(token->next, pipe_fd, root);
        }
        if (search_builtins_token(token, envp_list))
            return (exit(EXIT_FAILURE), 0);
        else
        {
            // printf("\033[31;1mClose FD 1 : %d (child process : %d)\033[m\n", pipe_fd[WRITE], getpid());
            // close(pipe_fd[WRITE]);
            // tmp_arg = ft_split(token->value, ' ');
            path = test_good_path_for_exec(token->value[0], search_path(envp_list));
            tmp_envp = convert_envp(envp_list);
            if (execve(path, token->value, tmp_envp) < 0)
            {
                ft_error_exec("command not found\n", token->value[0]);
                free_everything(&root, NULL);
                // free_tab((void**)tmp_arg);
                free_tab((void**)tmp_envp);
                free_envp(&envp_list);
                exit(EXIT_FAILURE);
            }
        }
    }
    else if (id > 0)
    {
        printf("\033[31;1mClose FD 1 : %d (parent process : %d)\033[m\n", pipe_fd[WRITE], getpid());
        close(pipe_fd[WRITE]);
        // printf("\033[31;1mClose FD 0 : %d (parent process : %d)\033[m\n", pipe_fd[READ], getpid());
        // close(pipe_fd[READ]);
        waitpid(id, &status, 0);
        return (0);
    }
    else
    {
        perror("fork");
    }
    return (0);
}


int execute_pipeline(t_lexer *node,int *pipe_fd, t_envp *envp_list, t_lexer *root)
{
    int fd_in;
    int status;
    pid_t id;

    if (node->type != PIPE)
        return (-1);
    close(pipe_fd[WRITE]);
    // close(pipe_fd[READ]);
    fd_in = pipe_fd[READ];
    if (pipe(pipe_fd) < 0)
        return (-1);
    printf("\033[32;1mREAD : %d || WRITE : %d\033[m\n",pipe_fd[READ], pipe_fd[WRITE]);
    id = fork();
    if (id < 0)
        return (-1);
    if (id == 0)
    {
        printf("\033[35;1mfd_in : %d\033[m\n", fd_in);
        dup2(fd_in, STDIN_FILENO);
        close(fd_in);
        execute_ast(node->next, pipe_fd ,envp_list, root);
        exit(EXIT_FAILURE);
    }
    else
    {
        close(fd_in);
        close(pipe_fd[READ]);
        close(pipe_fd[WRITE]);
        waitpid(id, &status, 0);
    }
    return (0);
}

int ft_redirection(t_lexer *node, int *pipe_fd, t_lexer *root)
{
	if	(node->type >= 6 && node->type <= 9)
    {
        ft_red_out(node);
        ft_red_append(node);
        ft_red_in(node);
        if (ft_heredoc(node, pipe_fd, root))
            return (1);
    }
    printf("out\n");
	return (0);
}

int execute_ast(t_lexer *node,int pipe_fd[2], t_envp *envp_list, t_lexer *root)
{
    if (!node)
        return (close(pipe_fd[READ]), close(pipe_fd[WRITE]), 1);
    if (how_many_cmd(root) == 1)
    {
        if (search_builtins_token(root, envp_list))
            return (close(pipe_fd[READ]), close(pipe_fd[WRITE]), 0);
    }
    if (node->type == CMD)
        execute_command(node, pipe_fd, envp_list, root);
    else if (node->type == PIPE)
        return (execute_pipeline(node, pipe_fd,envp_list, root));
    else if (node->type >= 6 && node->type <= 9)
	{
        if (ft_redirection(node, pipe_fd, root))
        {
            return (0);
        }
	}
    execute_ast(node->next, pipe_fd ,envp_list, root);
    return (0);
}


// int execute_ast(t_lexer *node,int pipe_fd[2], t_envp *envp_list)
// {
//     t_lexer *root;
//     if (!node)
//         return (1);
//     root = node;
//     while (node)
//     {
//         if ()
//         if (node->type != 1)
//             fprintf(stderr ,"\033[31;1m\n\nStart new node (%s + %d)\033[m\n\n", node->value, node->type);
//         if (node->type == CMD)
//             execute_command(node, pipe_fd, envp_list);
//         else if (node->type == PIPE)
//             return (execute_pipeline(node, pipe_fd, envp_list));
//         node = node->next;
//     }
//     return (0);
// }