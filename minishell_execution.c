/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:17 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/04/17 16:02:00 by ldoppler         ###   ########.fr       */
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

void    execution_pipe(t_cmd *cmd)
{
    execve(cmd->pathname, cmd->arg, NULL);
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
        i++;
    }
    printf("Value i : %d\n\n", i);
    /*Malloc my pipes*/
    (*cmd)->tab_ref->pipe_fd = malloc(sizeof(int*) * 4);
    for (int i = 0; i < 4; i++)
    {
        (*cmd)->tab_ref->pipe_fd[i] = malloc(sizeof(int) * 2);
    }
    for (int i = 0; i < 4; i++)
    {
        pipe((*cmd)->tab_ref->pipe_fd[i]);
    }
    /* Malloc the number of child process */
    (*cmd)->tab_ref->process_id = malloc(sizeof(pid_t) * i);
    while (j < i)
    {
        (*cmd)->tab_ref->process_id[j] = fork();
        if ((*cmd)->tab_ref->process_id[j] == 0)
        {
            //Child process
            printf("\033[1;32mChild process %d\033[m\n", j);
            execution_pipe(cmd[j]);
            exit(EXIT_SUCCESS);
        }
        j++;
    }
    wait(NULL);
    printf("Parent process\n");
}