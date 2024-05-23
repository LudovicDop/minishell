/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:17 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/23 17:59:34 by ldoppler         ###   ########.fr       */
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
    char    **tmp_envp;
    //Child process
    // if (cmd->any_redirection)
    // {
    //     fprintf(stderr, "AXA\n");
    //     special_carac(cmd);
    // }

    // if (search_builtins_cmd(cmd))
    //     return ;
    // if (execve(cmd->pathname, cmd->arg, NULL) < 0)
    // {
    //     perror("execve");
    // }
    tmp_arg = ft_split(cmd->arg, ' ');
    //fprintf(stderr, "tmp_arg[0] : %s\n", tmp_arg[1]);
    cmd->pathname = test_good_path_for_exec(tmp_arg[0], search_path(&cmd));
    tmp_envp = convert_envp(cmd->envp_ref);
    if (execve(cmd->pathname, tmp_arg, tmp_arg) < 0)
    {
        perror("execve");
    }
    
}

void    execution_main(t_cmd **cmd)
{
    t_cmd   *cmd_list;
    int nbre_cmd;
    int fd_in;
    int i;

    i = 0;
    fd_in = 0;
    cmd_list = *cmd;
    nbre_cmd = how_many_cmd(cmd_list);
    cmd_list->tab_ref->process_id = malloc(sizeof(pid_t) * nbre_cmd);
    while (cmd_list)
    {
        pipe(cmd_list->tab_ref->pipe_fd);
        cmd_list->tab_ref->process_id[i] = fork();
        if (cmd_list->tab_ref->process_id[i] == 0)
        {
            close(cmd_list->tab_ref->pipe_fd[0]);
            dup2(fd_in, STDIN_FILENO);
            if (i < nbre_cmd - 1)
            {
                dup2(cmd_list->tab_ref->pipe_fd[1], STDOUT_FILENO);
            }
            close(cmd_list->tab_ref->pipe_fd[1]);
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
    close(fd_in);
    cmd_list = *cmd;
    i = 0;
    while (i < nbre_cmd)
    {
        waitpid(cmd_list->tab_ref->process_id[i], 0, WNOHANG);
        i++;
    }
    wait(NULL);
}
