/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/05/03 19:35:35 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pre_alloc(t_cmd **cmd, t_tab *glob, char **envp)
{
    for(int i = 0; i < 3; i++)
    {
        cmd[i] = malloc(sizeof(t_cmd));
        printf("\033[31;1mcmd[%d] : %p!\033[m\n",i, &cmd[i]);
    }
    printf("\n");

    for (int i = 0; i < 3; i++)
    {
        (cmd[i])->arg = malloc(sizeof(char*) * 100);
    }
    printf("\033[31;1mcmd[%d].arg = %p\033[m\n",0, (*cmd)->arg);
    printf("\n");
    for (int i = 0; i < 3; i++)
    {
        (*cmd[i]).tab_ref = glob;
        printf("\033[31;1m(*cmd[%d]).tab_ref : %p\033[m\n", i, &(*cmd[i]).tab_ref);
    }
    printf("\n");
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
        pre_alloc(cmd, glob, envp);
        (*cmd)->tab_ref->tmp = readline("===>");
        add_history((*cmd)->tab_ref->tmp);
        start_parsing((*cmd)->tab_ref->tmp, cmd);
        execution_main(cmd);
        free_everything(cmd);
     }
    return (0);
}



