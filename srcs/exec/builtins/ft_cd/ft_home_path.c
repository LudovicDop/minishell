/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_home_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:48:38 by ldoppler          #+#    #+#             */
/*   Updated: 2024/06/05 16:47:57 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// string, $, AXA
// ceci est un $ test de test
char *search_and_replace(char *string, char c_to_replace, char *insert)
{
    int i;
    int j;
    int k;
    int lenght_string;
    char *new_string;

    i = 0;
    j = 0;
    k = 0;
    if (!string || !c_to_replace || !insert)
        return (string);
    lenght_string = ft_strlen(string);
    while (string[i])
    {
        if (string[i] == c_to_replace)
            break ;
        i++; 
    }
    if (i != lenght_string)
    {
        i = 0;
        printf("result : %lu\n", lenght_string + ft_strlen(insert) + 1);
        new_string = malloc(sizeof(char) * lenght_string + ft_strlen(insert) + 1);
        while (string[i])
        {
            if (string[i] == c_to_replace)
            {
                i++;
                printf("len : %zu (%s)\n", ft_strlen(insert), insert);
                while (insert[j])
                {
                    new_string[k] = insert[j];
                    printf("new_string bis: %c\n", new_string[k]);
                    k++;
                    j++;
                }
            }
            new_string[k] = string[i];
            printf("new_string : %c\n", new_string[k]);
            k++;
            if (string[i])
                i++;
        }
        new_string[k] = '\0';
        printf("new_string : %c\n", new_string[k]);
        return (new_string);
    }
    return (string);
}

void    home_path(char *path)
{
    printf("\033[35;1m%s\033[m\n", search_and_replace("TEST$ TEST$", '$', "bien joue"));
    printf("home_path : %s\n", path);
}