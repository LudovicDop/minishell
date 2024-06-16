/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:16:35 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/16 13:58:33 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_error_msg(t_cmd *cmd, char *error_msg, char near_this_char, int error_val)
{
    if (!error_msg || !near_this_char)
        return (1);
    ft_putstr_fd("nemshell : ", 2);
    ft_putstr_fd(error_msg, 2);
    ft_putstr_fd("'", 2);
    ft_putchar_fd(near_this_char, 2);
    ft_putstr_fd("'\n", 2);
    // cmd->tab_ref->return_val = error_val;
    return (0);
}