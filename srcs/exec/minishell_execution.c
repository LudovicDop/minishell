/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:17 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/03 18:56:21 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_print_my_arg(char **arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        printf("\033[1;34mexecution_cmd_arg : \033[1;32m%s\033[m\033[m\n", arg[i]);
        i++;
    }
}

void    ft_print_my_redirection(char **arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        printf("\033[1;33mredirection_cmd_arg : \033[1;36m%s\033[m\033[m\n", arg[i]);
        i++;
    }
}

/*File fd[1] == Writing && fd[0] == Reading */
void    execution_pipe(t_cmd *cmd, int j)
{
    //Child process
    if (cmd->any_redirection)
    {
        special_carac(cmd);
    }

    if (search_builtins_cmd(cmd))
        return ;
    if (execve(cmd->pathname, cmd->arg, NULL) < 0)
    {
        perror("execve");
    }
}

void    close_fd(int **p_fd, int nbre_of_pipe)
{
    int i;

    i = 0;
    while (i < nbre_of_pipe)
    {
        close(p_fd[i][0]);
        close(p_fd[i][1]);
        i++;
    }
}
/*Objectif gerer plusieurs pipes peut être faire une sorte de buffer pour stock la partie read de mon fd de pipe*/
void    execution_main(t_cmd **cmd)
{
    int fd_in;
    int i;
    int j;

    fd_in = 0;
    i = 0;
    j = 0;
    fprintf(stderr, "\033[34;1m\nSTART Execution\033[m\n\n");
    /*Just printing the content of my struct*/
    while (cmd[i])
    {
        printf("\033[1;31mPATH_NAME : %s \033[m\n", (*cmd[i]).pathname);
        ft_print_my_arg((*cmd[i]).arg);
        if ((*cmd[i]).any_redirection)
            ft_print_my_redirection((*cmd[i]).arg_redirection);
        i++;
    }
    printf("Value i : %d\n\n", i);
    /*Malloc my pipes*/
    // (*cmd)->tab_ref->pipe_fd = malloc(sizeof(int) * 2);
    /* Malloc the number of child process */
    (*cmd)->tab_ref->process_id = malloc(sizeof(pid_t) * i);
    while (j < i)
    {
        pipe((*cmd)->tab_ref->pipe_fd);
        (*cmd)->tab_ref->process_id[j] = fork();
        if ((*cmd)->tab_ref->process_id[j] == 0)
        {
            //Child process
            fprintf(stderr, "\033[1;32mChild process %d (id : %d)\033[m\n", j, getpid());
            dup2(fd_in, STDIN_FILENO);
            if (j + 1 != i)
            {
                dup2((*cmd)->tab_ref->pipe_fd[1], STDOUT_FILENO);
            }
            execution_pipe(cmd[j], j);
            exit(EXIT_SUCCESS);
        }
        else
        {
            wait(NULL);
            close((*cmd)->tab_ref->pipe_fd[1]);
            fd_in = (*cmd)->tab_ref->pipe_fd[0];
        }
        j++;
    }
}
