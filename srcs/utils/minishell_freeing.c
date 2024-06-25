/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_freeing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:12:00 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/25 10:21:11 by ldoppler         ###   ########.fr       */
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

void    free_everything(t_cmd **cmd, char *prompt)
{
    t_cmd *current;

    current = *cmd;
    if (current)
    {
        free(current->tab_ref->process_id);
        free(current->tab_ref);
        free_cmd_list(&current);
    }
    if (prompt)
        free(prompt);
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

void    free_pwd_lst(t_pwd **pwd)
{
    t_pwd *current;
    t_pwd *to_free;
    
    current = *pwd;
    while (current)
    {
        to_free = current;
        current = current->next;
        free(to_free->node);
        free(to_free);
    }
}

