/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_freeing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:12:00 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/26 01:02:35 by ludovicdopp      ###   ########.fr       */
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

/*Not update for the moment but we will use it later*/
void    free_everything(t_cmd **cmd)
{
    free((*cmd)->tab_ref->process_id);
    free((*cmd)->tab_ref);
    free_tab((void**)cmd);
}


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

