/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:17 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/22 11:14:48 by ldoppler         ###   ########.fr       */
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
    tmp_arg = ft_split(cmd->arg, ' ');
    printf("tmp_arg[0] : %s\n", tmp_arg[0]);
    cmd->pathname = test_good_path_for_exec(tmp_arg[0], search_path(&cmd));
    printf("\033[35;1mpathname : %s\033[m\n",cmd->pathname);
    if (execve(cmd->pathname, tmp_arg, NULL) < 0)
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
    int     i;
    int     nbre_cmd;
    int     fd_in;
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
        close(tmp->tab_ref->pipe_fd[0]);
        close(tmp->tab_ref->pipe_fd[1]);
        tmp->tab_ref->process_id[i] = fork();
        if (tmp->tab_ref->process_id[i] == 0)
        {
            //Child process 
            printf("\033[32;1mChild process! (i : %d)\033[m\n", i);
            dup2(STDIN_FILENO, fd_in);
            if (i + 1 != nbre_cmd)
                dup2(tmp->tab_ref->pipe_fd[1], STDOUT_FILENO);
            execution_pipe(tmp);
            exit(EXIT_SUCCESS);
        }
        else
        {
            //Parent process
            fd_in = tmp->tab_ref->pipe_fd[0];
            dup2(fd_in, STDIN_FILENO);
        }
        tmp = tmp->next;
        i++;
    }
    i = 0;
    printf("Nbre cmd : %d\n", nbre_cmd);
    while(i < nbre_cmd)
    {
        printf("process id : %d\n", tmp->tab_ref->process_id[i]);
        waitpid(tmp->tab_ref->process_id[i], 0, 0);
        i++;
    }
}
