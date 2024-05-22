/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/05/22 15:24:36 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_cmd_list(t_cmd **cmd_list)
{
    t_cmd *current;
    t_cmd *to_free;

    current = *cmd_list;
    while (current)
    {
        to_free = current;
        current = current->next;
        if (to_free->any_redirection)
            free(to_free->arg_redirection);
        free(to_free->arg);
        free(to_free->pathname);
        free(to_free);
    }
}

void free_global_var(t_tab **global)
{
    t_tab *current;
    t_tab *to_free;

    current = *global;
    free(current->process_id);
    free(current->prompt);
    free(current);
}

void    free_envp(t_envp **envp)
{
    t_envp *current;
    t_envp *to_free;
    
    current = *envp;
    while (current)
    {
        to_free = current;
        current = current->next;
        free(to_free->key);
        free(to_free->value);
        free(to_free);
    }
}

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
    init_envp(&envp_list ,envp);

     while (1)    
     {
        cmd_list = NULL;    
        prompt = get_prompt(envp_list);
        input_cmd = readline(prompt);
        start_parsing(input_cmd, &cmd_list, &envp_list);
        // while (cmd)
        // {
        //     printf("\033[32;1m Arg : %s\033[m\n", cmd->arg);
        //     if (cmd->any_redirection)
        //         printf("\033[32;1m Arg_redirection : %s\033[m\n", cmd->arg_redirection);
        //     cmd = cmd->next;
        // }

        // while (cmd_list)
        // {
        //     printf("key : %s\n", cmd_list->envp_ref->key);
        //     cmd_list = cmd_list->next;
        // }

        add_history(input_cmd);
        execution_main(&cmd_list);

        
        //free_envp(&envp_list);
        //free_global_var(&cmd_list->tab_ref);
        free_cmd_list(&cmd_list);


        
    //     if (!(*cmd)->tab_ref->tmp)
    //     {
    //         free_everything(cmd);
    //         break;
    //     }
    //     free_everything(cmd);
   }
    return (0);
}



