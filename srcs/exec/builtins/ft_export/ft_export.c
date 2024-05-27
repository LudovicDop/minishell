/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:37:53 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/27 16:51:37 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_key(char *string)
{
    int i;
    char new_string;

    i = 0;
    if (!string)
        return (NULL);
    while (string[i] != '=')
    {
        
    }
    
}

t_envp **search_envp_key(t_envp **envp, char *key)
{
    t_envp *current;

    current = *envp;
    while (current)
    {
        if (!ft_strcmp(current->key, key))
        {
            fprintf(stderr, "\033[36;1mJust find the key\033[m\n");
            return (&current);
        }
        current = current->next;
    }
    fprintf(stderr, "\033[31;1mNothing was found!\033[m\n");
    return (NULL);
}

void    ft_export(t_envp **envp_list, char *key)
{
    char *tmp_key;

    if (!envp_list)
        return ;
    fprintf(stderr, "\033[36;1mkey : %s\033[m\n", key);
    tmp_key = get_key(key);
    fprintf(stderr, "key : %s\n", tmp_key);
    //search_envp_key(envp_list, key);
}