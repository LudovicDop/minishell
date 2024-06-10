/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:37:53 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/10 15:50:39 by ldoppler         ###   ########.fr       */
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

char *get_key_envp(const char *s1)
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

void    ft_export(t_envp **envp_list, char *key_value)
{
    t_export exp_tmp;

    if (!key_value)
    {
        print_env_export(envp_list);
        return ;
    }
    printf("\033[36;1mkey_value = %s\033[m\n", key_value);
    exp_tmp.value = ft_strdup(get_value(key_value));
    exp_tmp.key = ft_strdup(get_key_envp(key_value));
    fprintf(stderr ,"\033[36;1mKey : %s && Value : %s\033[m\n", exp_tmp.key, exp_tmp.value);
    search_key_and_replace_it(envp_list, exp_tmp.key, exp_tmp.value);
}