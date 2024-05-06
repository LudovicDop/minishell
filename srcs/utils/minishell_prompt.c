/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:15:46 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/05 14:42:52 by ludovicdopp      ###   ########.fr       */
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
    while (*s1 != '/')
        s1++;
    new_path = s1;
    return (new_path);
}

// char *get_prompt(t_cmd *cmd)
// {
//     char    *tmp_user;
//     char    *tmp_path;

//     tmp_user = NULL;
//     tmp_path = NULL;
//     if (!cmd)
//         return (NULL);
//     tmp_user = getenv("USER");
//     tmp_path = getenv("PWD");

//     cmd->tab_ref->prompt = ft_strjoin("\033[32;1m@", tmp_user);
//     cmd->tab_ref->prompt = ft_strjoin2(cmd->tab_ref->prompt, "\033[m:");
//     cmd->tab_ref->prompt = ft_strjoin2(cmd->tab_ref->prompt, "\033[35;1m");
//     cmd->tab_ref->prompt = ft_strjoin2(cmd->tab_ref->prompt, remove_users(tmp_path));
//     cmd->tab_ref->prompt = ft_strjoin2(cmd->tab_ref->prompt, "$\033[m ");
    
//     return (cmd->tab_ref->prompt);
// }

void get_prompt(void)
{
    char    *ret_prompt;
    char    *tmp_user;
    char    *tmp_path;

    tmp_user = NULL;
    tmp_path = NULL;
    tmp_user = getenv("USER");
    tmp_path = getenv("PWD");

    ret_prompt = ft_strjoin("\033[32;1m@", tmp_user);
    ret_prompt = ft_strjoin2(ret_prompt, "\033[m:");
    ret_prompt = ft_strjoin2(ret_prompt, "\033[35;1m");
    ret_prompt = ft_strjoin2(ret_prompt, remove_users(tmp_path));
    ret_prompt = ft_strjoin2(ret_prompt, "$\033[m ");
    
    printf("%s", ret_prompt);
    free(ret_prompt);
}
