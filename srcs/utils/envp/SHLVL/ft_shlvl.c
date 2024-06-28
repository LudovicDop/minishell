/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:27:01 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/28 14:20:46 by ldoppler         ###   ########.fr       */
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
    if (node)
    {
        shlvl = ft_atoi(node->value);
        shlvl++;
        free(node->value);
        node->value = ft_itoa(shlvl);
    }
    else
    {
        search_key_and_replace_it(envp, "SHLVL", "1");
    }
}