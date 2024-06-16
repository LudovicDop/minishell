/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_symbol.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 10:26:21 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/16 13:58:17 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    check_redirection_bis(char *input_cmd, char symbol)
{
    int i;
    int count_symbol;

    count_symbol = 0;
    i = 0;
    if (!input_cmd)
        return (0);
    while (input_cmd[i])
    {
        if (input_cmd[i] == '\'' || input_cmd[i] == '"')
        {
            while (input_cmd[i] && (input_cmd[i] != '\'' || input_cmd[i] != '"'))
                i++;
        }
        if (input_cmd[i] == symbol)
        {
            count_symbol = 0;
            while (input_cmd[i] && input_cmd[i] == symbol)
            {
                count_symbol++;
                i++;
            }
            if (count_symbol > 2)
                return (1);
            if (empty_after_symbol(&input_cmd[i]))
                return (1);
        }
        if (input_cmd[i])
            i++;
    }
    return (0);
}

int    check_redirection_symbol(char *input_cmd, t_cmd *cmd)
{
    if (check_redirection_bis(input_cmd, '<'))
    {
        ft_error_msg(cmd, "syntax error near unexpected token ", '<', 2);
        return (1);
    }
    if (check_redirection_bis(input_cmd, '>'))
    {
        ft_error_msg(cmd, "syntax error near unexpected token ", '>', 2);
        return (1);
    }
    return (0);
}