/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:09:55 by ldoppler          #+#    #+#             */
/*   Updated: 2024/06/12 16:42:19 by ludovicdopp      ###   ########.fr       */
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