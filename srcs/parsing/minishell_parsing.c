/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:24:09 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/04/28 18:10:10 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ping -c 5 google.com | grep "rtt" 

char    *test_good_path_for_exec(char *exec_name, char *path)
{
    int     i;
    char    *tmp;
    char    *tmp_bis;
    char    **split_path;

    split_path = ft_split(path, ':');
    i = 0;
    while (split_path[i])
    {
        tmp_bis = ft_strjoin(split_path[i], "/");
        tmp = ft_strjoin(tmp, exec_name);
        if (access(tmp, F_OK) == 0)
        {
            printf("\033[32;1mSucces! %s\033[m\n", tmp);
            free(tmp_bis);
            free_tab((void**)split_path);
            return (tmp);
        }
        free(tmp_bis);
        free(tmp);
        i++;
    }
    free_tab((void**)split_path);
    return (NULL);
}

char    *search_path(t_cmd **cmd)
{
    int i;

    i = 0;
    printf("\033[36;1mSTART function search_path!\033[m\n");

    while ((*cmd)->tab_ref->envp[i])
    {
        if (ft_strncmp((*cmd)->tab_ref->envp[i], "PATH=", sizeof(char) * 5) == 0)
        {
            return ((*cmd)->tab_ref->envp[i] + 5);
        }
        i++;
    }
    return (NULL);
}
void    init_env_path(t_cmd **cmd)
{
    int i;

    i = 0;
    while (cmd[i])
    {
        (cmd[i]->pathname) = test_good_path_for_exec(cmd[i]->arg[0], search_path(cmd));
        i++;
    }
}
void    start_parsing(char *tmp, t_cmd **cmd)
{
    printf("\033[34;1m\nSTART Parsing\033[m\n");
    printf("\n");
    int i;
    int k;
    int j;
    char **buffer;

    i = 0;
    k = 0;
    j = 0;
    buffer = ft_split(tmp, ' ');
    if (!buffer || !cmd)
        return;
    while (buffer[i])
    {
        if (buffer[i] && buffer[i][0] == '|')
        {
            (*cmd[j]).arg[k] = NULL;
            printf("\033[31;1mcmd[%d].arg[%d] = %s\033[m\n",j,k, (*cmd[j]).arg[k]);
            j++;
            i++;
            k = 0;
        }
        (*cmd[j]).arg[k] =  ft_strdup(buffer[i]);
        printf("\033[31;1mcmd[%d].arg[%d] = %s (address : %p)\033[m\n",j,k, (*cmd[j]).arg[k], &(*cmd[j]).arg[k]);
        k++;
        i++;
    }
    printf("j = %d\n",j + 1);
    (*cmd[j]).arg[k] = NULL;
    printf("\033[31;1mcmd[%d].arg[%d] = %s\033[m\n",j,k, (*cmd[j]).arg[k]);
    cmd[j + 1] = NULL;
    init_env_path(cmd);
    free_tab((void**)buffer);
}
