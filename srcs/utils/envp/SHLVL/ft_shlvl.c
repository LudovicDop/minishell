/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:27:01 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/12 14:10:15 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_envp				*search_envp_key(t_envp **envp, char *key)
{
    t_envp *i;

    i = *envp;
    while (i)
    {
        if (!ft_strcmp(i->key, "SHLVL"))
            return (i);
        i = i->next;
    }
    return (NULL);
}

void    increment_shlvl(t_envp **envp)
{
    t_envp *node;
    int shlvl;

    node = search_envp_key(envp, "SHLVL");
    shlvl = ft_atoi(node->value);
    shlvl++;
    free(node->value);
    node->value = ft_itoa(shlvl);
}