/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:17:12 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/12 13:04:40 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    init_swap_value(char *tmp_key, char *tmp_value, t_envp *i, t_envp *j)
{
    tmp_value = i->value;
    tmp_key = i->key;
    i->key = j->key;
    i->value = j->value;
    j->key = tmp_key;
    j->value = tmp_value;
}

void   sort_list(t_envp **envp)
{
    t_envp *i;
    t_envp *j;
    char *tmp_key;
    char *tmp_value;

    if (!envp)
        return ;
    i = *envp;
    while (i)
    {
        j = i->next; 
        while (j)
        {
            if (ft_strncmp(i->key, j->key, ft_strlen(i->key) + ft_strlen(j->key)) > 0)
                init_swap_value(tmp_key, tmp_value, i, j);
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