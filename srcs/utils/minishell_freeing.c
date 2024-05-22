/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_freeing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:12:00 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/22 10:47:47 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_tab(void   **my_tab)
{
    int i;

    i = 0;
    if (!my_tab)
        return ;
    while (my_tab[i])
    {
        free(my_tab[i]);
        i++;
    }
    free(my_tab);
}

void    free_arg(t_cmd **cmd)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (cmd[i])
    {
        j = 0;
        while (cmd[i]->arg[j])
        {
            // free(cmd[i]->arg[j]);
            j++;
        }
        free(cmd[i]->arg);
        i++;
    }
}

void    free_path(t_cmd **cmd)
{  
    int i;

    i = 0;
    while (cmd[i])
    {
        free(cmd[i]->pathname);
        i++;
    }
}
void    free_everything(t_cmd **cmd)
{
    // free_envp((&(*cmd)->tab_ref->envp));
    free((*cmd)->tab_ref->process_id);
    free((*cmd)->tab_ref);
    free_arg(cmd);
    free_path(cmd);
    free_tab((void**)cmd);
}
