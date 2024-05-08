/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:16:18 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/08 20:14:13 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_env(t_cmd *cmd)
{
    while (cmd->tab_ref->envp)
    {
        printf("%s",cmd->tab_ref->envp->key);
        printf("%s\n", cmd->tab_ref->envp->value);
        cmd->tab_ref->envp = cmd->tab_ref->envp->next;
    }
    free_envp(&(cmd->tab_ref->envp));
    free_everything(&cmd);
}
void    ft_echo(t_cmd *cmd)
{
    printf("%s\n", cmd->arg[1]);
}

void    ft_cd(t_cmd *cmd)
{
    if (chdir(cmd->arg[1]) < 0)
    {
        perror("chdir");
    }
}
int search_builtins_cmd(t_cmd *cmd)
{
    //printf("\033[32;1mBEGIN (process : %d)\033[m\n",getpid());
    if (!ft_strcmp(cmd->arg[0], "cd"))
    {
        fprintf(stderr, "\033[36;1mStarting executing cd command!\033[m\n");
        ft_cd(cmd);
        return (1);
    }
    else if (!ft_strcmp(cmd->arg[0], "echo"))
    {
        fprintf(stderr, "\033[36;1mStarting executing echo command!\033[m\n");
        ft_echo(cmd);
        return (1);
    }
    else if (!ft_strcmp(cmd->arg[0], "pwd"))
    {
        fprintf(stderr, "\033[36;1mStarting executing pwd command!\033[m\n");
        return (1);
    }
    else if (!ft_strcmp(cmd->arg[0], "export"))
    {
        fprintf(stderr, "\033[36;1mStarting executing export command!\033[m\n");
        return (1);
    }
    else if (!ft_strcmp(cmd->arg[0], "unset"))
    {
        fprintf(stderr, "\033[36;1mStarting executing unset command!\033[m\n");
        return (1);
    }
    else if (!ft_strcmp(cmd->arg[0], "env"))
    {
        fprintf(stderr, "\033[36;1mStarting executing env command!\033[m\n");
        ft_env(cmd);
        return (1);
    }
    else if (!ft_strcmp(cmd->arg[0], "exit"))
    {
        fprintf(stderr, "\033[36;1mStarting executing exit command!\033[m\n");
        return (1);
    }
    //printf("\033[31;1mEXIT\033[m\n");
    return (0);
}
