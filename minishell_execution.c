/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:17 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/04/17 15:29:21 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_print_my_arg(char **arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        printf("\033[1;34mexecution_cmd_arg : \033[1;32m%s\033[m\033[m\n", arg[i]);
        i++;
    }
}

void    execution_main(t_cmd **cmd)
{
    int i;
    int j;

    i = 0;
    j = 0;
    /*Just printing the content of my struct*/
    while (cmd[i])
    {
        printf("\033[1;31mPATH_NAME : %s \033[m\n", (*cmd[i]).pathname);
        ft_print_my_arg((*cmd[i]).arg);
        i++;
    }
    printf("Value i : %d\n\n", i);
    /* Malloc the number of child process */
    (*cmd)->tab_ref->process_id = malloc(sizeof(pid_t) * i);
    while (j < i)
    {
        (*cmd)->tab_ref->process_id[j] = fork();
        printf("OK %d\n", j);
        if ((*cmd)->tab_ref->process_id[j] == 0)
        {
            //Child process
            printf("\033[1;32mChild process\033[m\n");
            exit(EXIT_SUCCESS);
        }
        j++;
    }

    printf("Parent process\n");

}