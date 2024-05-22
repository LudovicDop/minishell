/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:17 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/22 15:02:50 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int how_many_cmd(t_cmd *cmd_list)
{
    int nbre_of_cmd;

    nbre_of_cmd = 0;
    while (cmd_list)
    {
        nbre_of_cmd++;
        cmd_list = cmd_list->next;
    }
    return (nbre_of_cmd);
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


/*Objectif gerer plusieurs pipes peut être faire une sorte de buffer pour stock la partie read de mon fd de pipe*/
void    execution_main(t_cmd **cmd)
{
    t_cmd   *cmd_list;
    int fd_in;
    int i;

    i = 0;
    cmd_list = *cmd;
    cmd_list->tab_ref->process_id = malloc(sizeof(pid_t) * how_many_cmd(cmd_list));
    while (cmd_list)
    {
        pipe(cmd_list->tab_ref->pipe_fd);
        cmd_list->tab_ref->process_id[i] = fork();
        printf("i : %d\n", i);
        if (cmd_list->tab_ref->process_id[i] == 0)
        {
            close(cmd_list->tab_ref->pipe_fd[0]);
            fprintf(stderr, "\033[32;1mChild Process\033[m\n");
            if (i != 0)
            {
                dup2(fd_in, STDIN_FILENO);   
            }
            if (i != how_many_cmd(cmd_list) && how_many_cmd(cmd_list) != 1)
                dup2(cmd_list->tab_ref->pipe_fd[1], STDOUT_FILENO);
            execution_pipe(cmd_list);    
            exit(EXIT_SUCCESS);
        }
        else
        {
           close(cmd_list->tab_ref->pipe_fd[1]);
           fd_in = cmd_list->tab_ref->pipe_fd[0];
        }
        cmd_list = cmd_list->next;
        i++;
    }
    cmd_list = *cmd;
    i = 0;
    while (i < how_many_cmd(cmd_list))
    {
        printf("process id : %d\n", cmd_list->tab_ref->process_id[i]);
        waitpid(cmd_list->tab_ref->process_id[i], 0, 0);
        i++;
    }
}
