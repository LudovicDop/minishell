/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:37:53 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/11 00:01:26 by ludovicdopp      ###   ########.fr       */
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

void    search_key_and_increment_it(t_envp **envp, char *key, char *value)
{
    t_envp *i;

    i = *envp;
    if (!envp)
        return ;
    while (i)
    {
        if (!ft_strcmp(i->key, key))
        {
            i->value = ft_strjoin2(i->value, value);
        }
        i = i->next;
    }
    return ;
}

int     is_it_incrementation(char *key)
{
    int lenght;

    lenght = ft_strlen(key);
    if (key[lenght - 1] == '+')
    {
        key[lenght - 1] = '\0';
        return (1);
    }
    return (0);
}

void    ft_export(t_envp **envp_list, char *key_value)
{
    t_export exp_tmp;
    
    if (!key_value)
    {
        return (print_env_export(envp_list));
    }
    exp_tmp.value = ft_strdup(get_value(key_value));
    if (!exp_tmp.value)
        return ;
    exp_tmp.key = ft_strdup(get_key_envp(key_value));
    if (!exp_tmp.key)
        return ;
    if (is_it_incrementation(exp_tmp.key))
    {
        search_key_and_increment_it(envp_list, exp_tmp.key, exp_tmp.value);
        return ;
    }
    search_key_and_replace_it(envp_list, exp_tmp.key, exp_tmp.value);
}