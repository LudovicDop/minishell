/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:15:46 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/01 20:08:58 by ludovicdopp      ###   ########.fr       */
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
    while (*s1 != '\0'  && *s1 != '/')
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
    t_envp *current;

    current = envp_list;
    i = 0;
    while (current)
    {
        if (!ft_strcmp(current->key, "USER"))
        {
            tmp_user = ft_strjoin("\033[32;1m@", current->value);
            tmp_user = ft_strjoin2(tmp_user, "\033[m:");
        }
        if (*(current->value) != '\0' && !ft_strcmp(current->key, "PWD"))
        {
            tmp_path = ft_strjoin("\033[35;1m", remove_users(current->value));
            tmp_path = ft_strjoin2(tmp_path, "\033[m ");
            if (ft_strlen(tmp_path) == 11)
                tmp_path = ft_strdup("\033[35;1m/\033[m ");
        }
        else if (*(current->value) == '\0')
        {
            tmp_path = ft_strdup("\033[35;1m/\033[m");
        }
        current = current->next;
    }
    prompt = ft_strjoin(tmp_user, tmp_path);
    return (free(tmp_user), free(tmp_path), prompt);
}
