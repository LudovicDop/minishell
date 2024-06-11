/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:09:55 by ldoppler          #+#    #+#             */
/*   Updated: 2024/06/11 21:13:45 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_echo(char *string, bool without_ret)
{
    if (!string)
    {
        printf("\n");
        return ;
    }
    if (without_ret)
    {
        printf("%s", string);
    }
    else if (!without_ret)
    {
        printf("%s\n", string);
    }
}