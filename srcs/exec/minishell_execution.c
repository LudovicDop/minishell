/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:17 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/25 17:34:55 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_error_exec(char *error_msg, char *cmd_name)
{
    ft_putstr_fd("nemshell: ", 2);
    ft_putstr_fd(cmd_name, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(error_msg, 2);
}
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

void    execution_pipe(t_cmd *cmd)
{
    char    **tmp_arg;
    char    **tmp_envp;

    if (cmd->any_redirection)
    {
        special_carac(cmd);
    }
    if (search_builtins_cmd(cmd))
        return ;
    tmp_arg = ft_split(cmd->arg, ' ');
    cmd->pathname = test_good_path_for_exec(tmp_arg[0], search_path(&cmd));
    tmp_envp = convert_envp(cmd->envp_ref);
    if (execve(cmd->pathname, tmp_arg, tmp_envp) < 0)
    {
        ft_error_exec("command not found\n", tmp_arg[0]);
        free_tab((void**)tmp_arg);
        free_tab((void**)tmp_envp);
        return ;
        //need to free everything
    }
}

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

void    child_process(int fd_in, int nbre_cmd, t_cmd *cmd_list)
{
    close(cmd_list->tab_ref->pipe_fd[0]);
    dup2(fd_in, STDIN_FILENO);
    if (cmd_list->next)
        dup2(cmd_list->tab_ref->pipe_fd[1], STDOUT_FILENO);
    close(cmd_list->tab_ref->pipe_fd[1]);
    execution_pipe(cmd_list);
    // exit(EXIT_SUCCESS);
}

void    parent_process(t_cmd *cmd_list, int *fd_in, int i)
{
    close(cmd_list->tab_ref->pipe_fd[1]);
    *fd_in = cmd_list->tab_ref->pipe_fd[0];
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
    if (nbre_cmd == 0)
        return ;
    cmd_list->tab_ref->process_id = malloc(sizeof(pid_t) * nbre_cmd);
    if (nbre_cmd == 1)
    {
        if (search_builtins_cmd(cmd_list))
            return ;
    }
    while (cmd_list)
    {
        pipe(cmd_list->tab_ref->pipe_fd);
        cmd_list->tab_ref->process_id[i] = fork();
        if (cmd_list->tab_ref->process_id[i] == 0)
        {
            child_process(fd_in, nbre_cmd, cmd_list);
            free_everything(cmd, NULL);
            exit(EXIT_SUCCESS);
        }
        parent_process(cmd_list, &fd_in, i);
        cmd_list = cmd_list->next;
        i++;
    }
    close(fd_in);
    cmd_list = *cmd;
    wait_everyone(cmd_list, nbre_cmd);
}

int execute_command(t_token *token, int *pipe)
{
    char *tmp;

    if (token->type != CMD)
        return (-1);
    printf("\033[31;1mStart execution!\033[m\n");
    if (token->next)
    {
        close(pipe[0]);
        dup2(STDOUT_FILENO, pipe[1]);
        close(pipe[1]);
    }
    tmp = ft_split(token->value, ' ');
    execve()    
    return (0);
}

int execute_pipeline(t_token *node)
{
    if (node->type != PIPE)
        return (-1);
    printf("\033[32;1mStart pipe!\033[m\n");
    return (0);
}

int execute_ast(t_token *node)
{
    int pipe[2];

    if (!node)
        return (1);
    while (node)
    {
        if (node->type == CMD)
            execute_command(node, &pipe);
        else if (node->type == PIPE)
            execute_pipeline(node);
        node = node->next;
    }
    return (0);
}
