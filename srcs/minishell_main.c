/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/05/08 20:09:05 by ldoppler         ###   ########.fr       */
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

/*Command for test : cat fichier.txt |  sed s/Ceci/Anticonstitutionnellement/g | grep Anticons*/
int main(int argc, char **argv, char **envp)
{
    t_cmd **cmd;
    t_tab *glob;
    t_envp *envp_s;


    init_envp(&envp_s, envp);
    while (1)
    {
        cmd = malloc(sizeof(t_cmd));
        glob = malloc(sizeof(t_tab));
        ft_signal();
        pre_alloc(cmd, glob, envp_s);
        get_prompt();
        (*cmd)->tab_ref->tmp = readline("");
        start_parsing((*cmd)->tab_ref->tmp, cmd);
        add_history((*cmd)->tab_ref->tmp);
        execution_main(cmd);
        if (!(*cmd)->tab_ref->tmp)
        {
            free_everything(cmd);
            break;
        }
        free_everything(cmd);
     }
    return (0);
}



