/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:17 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/04/25 21:56:16 by ludovicdopp      ###   ########.fr       */
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
void    execution_pipe(t_cmd *cmd)
{
    //Child process
    if (!cmd->last_cmd)
        dup2(cmd->tab_ref->pipe_fd[1], STDOUT_FILENO);
    close(cmd->tab_ref->pipe_fd[0]);
    close(cmd->tab_ref->pipe_fd[1]);
    if (cmd->any_redirection)
    {
        special_carac(cmd);
    }

    //fprintf(stderr, "\033[1;31mBegin execution (process id : %d)\033[m\n",getpid());
    if (search_builtins_cmd(cmd))
        return ;
    //fprintf(stderr, "\033[32;1mcmd->path : %s && cmd->arg : %s\033[m\n",cmd->pathname, cmd->arg[0]);
    if (execve(cmd->pathname, cmd->arg, NULL) < 0)
    {
        perror("execve");
    }
}

void    execution_main(t_cmd **cmd)
{
    int i;
    int j;

    i = 0;
    j = 0;
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
    (*cmd)->tab_ref->pipe_fd = malloc(sizeof(int) * 2);
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
            if (j != 0)
            {
                fprintf(stderr, "\033[31;1mICI (process id : %d)\033[m\n", getpid());
                dup2((*cmd)->tab_ref->pipe_fd[0], STDIN_FILENO);
            }
            if (j + 1 == i)
            {
                (*cmd[j]).last_cmd = true;
            }
            execution_pipe(cmd[j]);
            exit(EXIT_SUCCESS);
        }
        j++;
    }
    wait(NULL);
    close((*cmd)->tab_ref->pipe_fd[0]);
    close((*cmd)->tab_ref->pipe_fd[1]);
}
