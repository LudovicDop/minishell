/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:51:18 by ldoppler          #+#    #+#             */
/*   Updated: 2024/06/11 18:45:39 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// modulo 256
void    ft_exit(char *val)
{
    unsigned int convert_val;

    convert_val = 0;
    if (!val)
    {
        exit(EXIT_SUCCESS);
    }
    convert_val = ft_atoi(val);
    convert_val %= 256;
    printf("\033[31;1mExit val : %u\033[m\n", convert_val);
    exit(convert_val);
}