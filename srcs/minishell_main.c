/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/05/30 15:02:42 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handler(int signal)
{
    if (signal == SIGINT)
    {
        printf("\n");
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
    else if (signal == SIGQUIT)
    {
        rl_on_new_line();
        rl_redisplay();
    }
}

void    init_signal(void)
{
    struct sigaction action;

    action.sa_handler = &handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);
}
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
    init_signal();
    while (1)    
    {
        cmd_list = NULL;
        prompt = get_prompt(envp_list);
        input_cmd = readline(prompt);
        if (!input_cmd)
        {
            exit(EXIT_SUCCESS);
        }
        start_parsing(input_cmd, &cmd_list, &envp_list);
        add_history(input_cmd);
        execution_main(&cmd_list);
        free_cmd_list(&cmd_list);
    }
     return (0);
}



