/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:24:09 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/04 11:05:49 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    start_parsing(char *tmp, t_cmd **cmd)
{
    int i;
    int k;
    int j;
    char **buffer;

    i = 0;
    k = 0;
    j = 0;
    if (!tmp || *tmp == '\0')
        return ;
    buffer = ft_split(tmp, ' ');
    if (!buffer || !cmd)
        return;
    while (buffer[i])
    {
        if (buffer[i] && buffer[i][0] == '|')
        {
            (*cmd[j]).arg[k] = NULL;
            j++;
            i++;
            k = 0;
        }
        (*cmd[j]).arg[k] =  ft_strdup(buffer[i]);
        k++;
        i++;
    }
    (*cmd[j]).arg[k] = NULL;
    cmd[j + 1] = NULL;
    init_env_path(cmd);
    free_tab((void**)buffer);
}
