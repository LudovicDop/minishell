/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:17 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/17 22:25:53 by ludovicdopp      ###   ########.fr       */
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
    char    **tmp_arg;
    //Child process
    // if (cmd->any_redirection)
    // {
    //     special_carac(cmd);
    // }

    // if (search_builtins_cmd(cmd))
    //     return ;
    // if (execve(cmd->pathname, cmd->arg, NULL) < 0)
    // {
    //     perror("execve");
    // }
    printf("\033[33;1mprocess id : %d\033[m\n",getpid());
    printf("\033[35;1mpathname : %s\033[m\n",cmd->arg);
    tmp_arg = ft_split(cmd->arg, ' ');
    // cmd->pathname = 
    // if (execve(cmd->pathname, tmp_arg, NULL) < 0)
    // {
    //     perror("execve");
    // }
    
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
    int     i;
    int     nbre_cmd;
    t_cmd *tmp;

    nbre_cmd = 0;
    i = 0;
    fprintf(stderr, "\033[31;1mStarting execution_main!\033[m\n");
    if (!*cmd)
        return ;
    tmp = *cmd;
    while (tmp)
    {
        tmp = tmp->next;
        nbre_cmd++;
    }
    tmp = *cmd;
    tmp->tab_ref->process_id = ft_calloc(nbre_cmd, sizeof(pid_t));
    /* 0- read && 1- write */
    while (i < nbre_cmd)
    {
        pipe(tmp->tab_ref->pipe_fd);
        tmp->tab_ref->process_id[i] = fork();
        if (tmp->tab_ref->process_id[i] == 0)
        {
            //Child process 
            printf("\033[32;1mChild process!\033[m\n");
            execution_pipe(tmp);
            exit(EXIT_SUCCESS);
        }
        else
        {
            //Parent process
        }
        tmp = tmp->next;
        i++;
    }
}
