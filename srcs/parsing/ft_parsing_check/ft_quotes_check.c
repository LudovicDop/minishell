/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 09:52:23 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/16 13:58:26 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     check_simple_quotes(char *input_cmd, t_cmd *cmd)
{
    int i;
    int count_quotes;

    i = 0;
    count_quotes = 0;
    while (input_cmd[i])
    {
       if (input_cmd[i] == '\'')
       {
            while (input_cmd[i] == '\'')
            {
                count_quotes++;
                i++;
            }
       }
       i++;
    }
    if (count_quotes % 2 != 0)
    {
        ft_error_msg(cmd, "syntax error near unexpected token ", '\'', 2);
        return (1);
    }
    return (0);
}

int     check_double_quotes(char *input_cmd, t_cmd *cmd)
{
    int i;
    int count_quotes;

    i = 0;
    count_quotes = 0;
    while (input_cmd[i])
    {
       if (input_cmd[i] == '"')
       {
            while (input_cmd[i] == '"')
            {
                count_quotes++;
                i++;
            }
       }
       if (input_cmd[i])
        i++;
    }
    if (count_quotes % 2 != 0)
    {
        ft_error_msg(cmd, "syntax error near unexpected token ", '"', 2);
        return (1);
    }
    return (0);
}