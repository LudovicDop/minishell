/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:15:46 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/21 16:30:34 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *remove_users(char *string)
{
    int  i = 0;
    char *s1;
    char *new_path;
    int  lenght;

    s1 = string;
    if (!*s1)
        return (NULL);
    s1++;
    s1++;
    while (*s1 != '/')
        s1++;
    new_path = s1;
    return (new_path);
}

char   *get_prompt(t_envp *envp_list)
{
    char    *tmp_user;
    char    *tmp_path;
    char    *prompt;
    int i;

    i = 0;
    while (envp_list)
    {
        if (!ft_strcmp(envp_list->key, "USER"))
        {
            tmp_user = ft_strjoin("\033[32;1m@", envp_list->value);
            tmp_user = ft_strjoin2(tmp_user, "\033[m:");
        }
        if (!ft_strcmp(envp_list->key, "PWD"))
        {
            tmp_path = ft_strjoin("\033[35;1m",remove_users(envp_list->value));
            tmp_path = ft_strjoin2(tmp_path, "\033[m ");
        }
        envp_list = envp_list->next;
    }
    prompt = ft_strjoin(tmp_user, tmp_path);
    return (free(tmp_user), free(tmp_path), prompt);
}
