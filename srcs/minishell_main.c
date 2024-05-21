/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/05/21 17:20:23 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pre_alloc(t_cmd **cmd, t_tab *glob,t_envp *envp_s)
{
    for(int i = 0; i < 3; i++)
    {
        cmd[i] = ft_calloc(1, sizeof(t_cmd));
    }
    printf("\n");

    for (int i = 0; i < 3; i++)
    {
        (cmd[i])->arg = ft_calloc(100, sizeof(char*));
        (cmd[i])->arg_redirection = ft_calloc(100, sizeof(char*));
    }
    for (int i = 0; i < 3; i++)
    {
        (*cmd[i]).tab_ref = glob;
    }
    glob->envp = envp_s;
}

/*Faire un liste chainee pour les cmd*/
/*Command for test : cat fichier.txt |  sed s/Ceci/Anticonstitutionnellement/g | grep Anticons*/
int main(int argc, char **argv, char **envp)
{
    char *input_cmd;
    char *prompt;
    t_cmd *cmd_list;
    t_envp *envp_list;

    envp_list = NULL;
    cmd_list = NULL;
    init_envp(&envp_list ,envp);

    // while (1)    
    // {
        prompt = get_prompt(envp_list);
        input_cmd = readline(prompt);
        printf("Address : %p\n", envp_list);
        start_parsing(input_cmd, &cmd_list, &envp_list);
        // while (cmd)
        // {
        //     printf("\033[32;1m Arg : %s\033[m\n", cmd->arg);
        //     if (cmd->any_redirection)
        //         printf("\033[32;1m Arg_redirection : %s\033[m\n", cmd->arg_redirection);
        //     cmd = cmd->next;
        // }
        // add_history(input_cmd);
        // execution_main(&cmd_list);
    //     if (!(*cmd)->tab_ref->tmp)
    //     {
    //         free_everything(cmd);
    //         break;
    //     }
    //     free_everything(cmd);
    //  }
    return (0);
}



