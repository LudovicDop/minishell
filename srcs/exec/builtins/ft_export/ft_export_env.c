/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:17:12 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/10 15:43:02 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void   sort_list(t_envp **envp)
{
    t_envp *i;
    t_envp *j;
    char *tmp;

    if (!envp)
        return ;
    i = *envp;
    while (i)
    {
        j = i->next; 
        while (j)
        {
            if (ft_strncmp(i->key, j->key, ft_strlen(i->key) + ft_strlen(j->key)) > 0)
            {
                tmp = i->key;
                i->key = j->key;
                j->key = tmp;
            }
            j = j->next;
        }
        i = i->next;
    }
    
    return ;
}

void    print_env_export(t_envp **envp)
{
    t_envp *tmp;

    if (!envp)
        return ;
    tmp = *envp;
    sort_list(&tmp);
    while (tmp)
    {
        printf("declare -x %s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}