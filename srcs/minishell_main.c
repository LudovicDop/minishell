/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/05/04 12:15:20 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pre_alloc(t_cmd **cmd, t_tab *glob, char **envp)
{
    for(int i = 0; i < 3; i++)
    {
        cmd[i] = malloc(sizeof(t_cmd));
    }
    printf("\n");

    for (int i = 0; i < 3; i++)
    {
        (cmd[i])->arg = malloc(sizeof(char*) * 100);
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
        //char *string = getenv("PWD");
        pre_alloc(cmd, glob, envp);
        get_prompt(*cmd);
        (*cmd)->tab_ref->tmp = readline((*cmd)->tab_ref->prompt);
        add_history((*cmd)->tab_ref->tmp);
        start_parsing((*cmd)->tab_ref->tmp, cmd);
        execution_main(cmd);
        free_everything(cmd);
     }
    return (0);
}



