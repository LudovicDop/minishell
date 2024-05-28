/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:37:53 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/28 12:36:58 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    search_key_and_replace_it(t_envp **envp, char *key, char *value)
{
    t_envp *envp_t;

    envp_t = *envp;
    while (envp_t)
    {
        if (!ft_strcmp(envp_t->key, key))
        {
            free(envp_t->value);
            envp_t->value = ft_strdup(value);
        }
        envp_t = envp_t->next;
    }
    return ;
}

char *get_key(const char *s1)
{
    int i;
    int j;
    char *string;
    char *ret;

    string = (char*)s1;
    i = 0;
    while (string[i] && string[i] != '=')
        i++;
    ret = ft_calloc(i + 1, sizeof(char));
    if (!ret)
        return (NULL);
    i = 0;
    while (string[i] && string[i] != '=')
    {
        ret[i] = string[i];
        i++;
    }
    ret[i] = '\0';
    return (ret);
}

char *get_value(const char *s1)
{
    return (ft_strchr2(s1, '='));
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

void    ft_export(t_envp **envp_list, char *key_value)
{
    t_export exp_tmp;

    exp_tmp.value = ft_strdup(get_value(key_value));
    exp_tmp.key = ft_strdup(get_key(key_value));
    fprintf(stderr ,"\033[36;1mKey : %s && Value : %s\033[m\n", exp_tmp.key, exp_tmp.value);
    search_key_and_replace_it(envp_list, exp_tmp.key, exp_tmp.value);
}