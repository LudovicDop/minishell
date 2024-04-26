/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:40:26 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/04/27 00:04:30 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
    int i;
    int s1_lenght;
    int s2_lenght;

    s1_lenght = ft_strlen(s1);
    s2_lenght = ft_strlen(s2);
    i = 0;

    while (i <= s1_lenght && i <= s2_lenght)
    {
        if (s1[i] != s2[i])
        {
            return (s1[i] - s2[i]);
        }
        i++;
    }
    return (0);
}

void    free_tab(void   **my_tab)
{
    int i;

    i = 0;
    if (!my_tab)
        return ;
    while (my_tab[i])
    {
        //printf("\033[32;1mcmd[%d].arg = %p (%s)\033[m\n", i, &my_tab[i], my_tab[i]);
        printf("\033[32;1mcmd[%d].arg = %p\033[m\n", i, &my_tab[i]);
        free(my_tab[i]);
        i++;
    }
    printf("\n");
    printf("my_tab address : %p\n", &my_tab);
    free(my_tab);
}

void    free_everything(t_cmd **cmd)
{
    int i = 0;
    free_tab((void**)(*cmd)->arg);
    free((*cmd)->pathname);
    free_tab((void**)cmd);
    printf("\033[32;1mcmd : %p\033[m\n", cmd);
    //free(cmd);
}
