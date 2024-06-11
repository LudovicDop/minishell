/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:51:18 by ldoppler          #+#    #+#             */
/*   Updated: 2024/06/11 20:27:04 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// modulo 256
void    ft_exit(t_cmd *cmd_list, char *val)
{
    unsigned int convert_val;

    convert_val = 0;
    if (!val)
    {
        cmd_list->tab_ref->return_val = 0;
        exit(EXIT_SUCCESS);
    }
    convert_val = ft_atoi(val);
    convert_val %= 256;
    cmd_list->tab_ref->return_val = convert_val;
    printf("\033[31;1mExit val : %u\033[m\n", cmd_list->tab_ref->return_val);
    exit(convert_val);
}