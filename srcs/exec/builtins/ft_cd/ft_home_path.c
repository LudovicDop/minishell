/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_home_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:48:38 by ldoppler          #+#    #+#             */
/*   Updated: 2024/06/05 21:48:47 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int c_is_present(char *string, char c)
{
    int i;

    i = 0;
    while (string[i])
    {
        if (string[i] == c)
            return (1);
        i++;
    }
    return (0);
}

char *start_replacing(char *string, char *new_string, char c_to_replace, char *insert)
{
    int i;
    int j;
    int k;

    k = 0;
    i = 0;
    j = 0;
    while (string[i])
    {
        if (string[i] == c_to_replace)
        {
            i++;
            while (insert[j])
                new_string[k++] = insert[j++];
        }
        new_string[k++] = string[i];
        if (string[i])
            i++;
    }
    new_string[k] = '\0';
    return (new_string);
}
// cd ~/Desktop
char *search_and_replace(char *string, char c_to_replace, char *insert)
{
    char *new_string;

    if (!string || !c_to_replace || !insert)
        return (string);
    if (c_is_present(string, c_to_replace))
    {
        new_string = malloc(sizeof(char) * ft_strlen(string) + ft_strlen(insert) + 1);
        if (!new_string)
            return (NULL);
        return (start_replacing(string, new_string, c_to_replace, insert));
    }
    new_string = ft_strdup(string);
    return (new_string);
}
void    remove_backslash_end(char **path)
{
    int i;

    i = 0;
    if (!*path)
        return ;
    i = ft_strlen(*path);
    if ((*path)[i - 1] == '/')
    {
        (*path)[i - 1] = '\0';
    }
}

void    home_path(char *path, t_envp **envp)
{
    char *new_path;
    char *tmp;

    tmp = NULL;
    new_path = NULL;
    //printf("\033[35;1m%s\033[m\n", search_and_replace(path, '~', getenv("HOME")));
    if (path)
    {
        new_path = search_and_replace(path, '~', getenv("HOME"));
    }
    else
        new_path = ft_strdup(getenv("HOME"));
    if (chdir(new_path) < 0)
    {
        perror("chdir");
        free(new_path);
        return ;
    }
    // printf("string before : %s\n", new_path);
    remove_backslash_end(&new_path);
    // printf("string : %s\n", tmp);
    search_key_and_replace_it(envp, "PWD", new_path);
    if (new_path)
        free(new_path);
    if (tmp)
        free(tmp);
    return ;
}
