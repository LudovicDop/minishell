/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:24:09 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/04/27 14:46:29 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ping -c 5 google.com | grep "rtt" 

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
    (*cmd[0]).pathname = ft_strdup("/sbin/ping");
    // (*cmd[1]).pathname = ft_strdup("/usr/bin/grep");
    cmd[j + 1] = NULL;
    free_tab((void**)buffer);
}