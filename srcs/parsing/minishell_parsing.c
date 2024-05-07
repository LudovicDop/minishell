/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:24:09 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/07 11:15:44 by ldoppler         ###   ########.fr       */
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
        if (buffer[i][0] == '>')
        {
            (*cmd[j]).any_redirection = true;
            (*cmd[j]).arg_redirection[0] = ft_strdup(buffer[i++]);
            (*cmd[j]).arg_redirection[1] = ft_strdup(buffer[i++]);
            printf("\033[31;1m(*cmd[%d]).arg_redirection[0] = %s\033[m\n", j, (*cmd[j]).arg_redirection[0]);
            printf("\033[35;1mExit value : %s\033[m\n", buffer[i]);
            if (buffer[i] == NULL)
                break;
        }
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
