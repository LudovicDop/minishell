/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/05/26 12:08:17 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// (ping -c 3 google.com | grep round-trip) || (cat error && echo success)
// (ping -c 3 google.com | grep round-trip) || cat error && echo success
int main(int argc, char **argv, char **envp)
{
    char *input_cmd;
    char *prompt;
    t_cmd *cmd_list;
    t_envp *envp_list;

    envp_list = NULL;
    init_envp(&envp_list ,envp);
    ft_export(&cmd_list);
    //  while (1)    
    //  {
        // cmd_list = NULL;
        // prompt = get_prompt(envp_list);
        // input_cmd = readline(prompt);
        // start_parsing(input_cmd, &cmd_list, &envp_list);
        // add_history(input_cmd);
        // execution_main(&cmd_list);
        //free_envp(&envp_list);
        //free_global_var(&cmd_list->tab_ref);
        // free_cmd_list(&cmd_list);
    //     if (!(*cmd)->tab_ref->tmp)
    //     {
    //         free_everything(cmd);
    //         break;
    //     }
    //     free_everything(cmd);
//    }
    // return (0);
}



