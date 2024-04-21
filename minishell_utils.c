/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:40:26 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/04/21 18:56:40 by ludovicdopp      ###   ########.fr       */
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

    printf("string 1 : %s\n", s1);
    while (i <= s1_lenght && i <= s2_lenght)
    {
        printf("s1[%d] : %c | s2[%d] : %c\n", i, s1[i], i, s2[i]);
        if (s1[i] != s2[i])
        {
            return (s1[i] - s2[i]);
        }
        i++;
    }
    printf("EXIT\n");
    return (0);
}
