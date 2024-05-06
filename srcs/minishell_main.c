/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/05/05 20:58:02 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pre_alloc(t_cmd **cmd, t_tab *glob, char **envp)
{
    for(int i = 0; i < 3; i++)
    {
        cmd[i] = ft_calloc(1, sizeof(t_cmd));
    }
    printf("\n");

    for (int i = 0; i < 3; i++)
    {
        (cmd[i])->arg = ft_calloc(100, sizeof(char*));
    }
    for (int i = 0; i < 3; i++)
    {
        (*cmd[i]).tab_ref = glob;
    }
    glob->envp = envp;
}


/*Command for test : cat fichier.txt |  sed s/Ceci/Anticonstitutionnellement/g | grep Anticons*/
int main(int argc, char **argv, char **envp)
{
    t_cmd **cmd;
    t_tab *glob;

    while (1)
    {
        cmd = malloc(sizeof(t_cmd));
        glob = malloc(sizeof(t_tab));
        ft_signal();
        pre_alloc(cmd, glob, envp);
        get_prompt();
        (*cmd)->tab_ref->tmp = readline("");
        start_parsing((*cmd)->tab_ref->tmp, cmd);
        if (!(*cmd)->tab_ref->tmp)
        {
            free_everything(cmd);
            break;
        }
        add_history((*cmd)->tab_ref->tmp);
        execution_main(cmd);
        free_everything(cmd);
     }
    return (0);
}



