/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:37:53 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/26 12:08:57 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp **search_envp_key(t_envp **envp, char *key)
{
    t_envp *current;

    current = *envp;
    while (current)
    {
        if (!ft_strcmp(current->key, key))
        {
            fprintf(stderr, "\033[36;1Just find the key\033[m\n");
            return (&current);
        }
        current = current->next;
    }
    fprintf(stderr, "\033[31;1mNothing was found!\033[m\n");
    return (NULL);
}

void    ft_export(t_cmd **cmd)
{
    if (!cmd)
        return ;
    search_envp_key(&((*cmd)->envp_ref), "PATH");
    
}