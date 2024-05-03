/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:40:26 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/03 19:44:20 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
    int i;
    int s1_lenght;
    int s2_lenght;

    s1_lenght = ft_strlen(s1);
    s2_lenght = ft_strlen(s2);
    i = 0;

    while (i <= s1_lenght && i <= s2_lenght)
    {
        if (s1[i] != s2[i])
        {
            return (s1[i] - s2[i]);
        }
        i++;
    }
    return (0);
}

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
            free(cmd[i]->arg[j]);
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
    free((*cmd)->tab_ref->process_id);
    free((*cmd)->tab_ref->tmp);
    free((*cmd)->tab_ref);
    free_arg(cmd);
    free_path(cmd);
    free_tab((void**)cmd);
}
