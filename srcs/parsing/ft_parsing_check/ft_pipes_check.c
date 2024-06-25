/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 10:17:07 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/16 13:58:30 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     empty_after_symbol(char *input_cmd)
{
    int i;

    i = 0;
    if (!input_cmd)
        return (0);
    while (input_cmd[i])
    {
        if (input_cmd[i] != ' ' && input_cmd[i]!= '\t' && input_cmd[i])
            return (0);
        i++;
    }
    if (input_cmd[i] == '\0')
        return (1);
    return (0);
}
int     check_pipes(char *input_cmd, t_cmd *cmd)
{
    int i;
    int count_pipes;

    count_pipes = 0;
    i = 0;
    if (!input_cmd)
        return (0);
    while (input_cmd[i])
    {
        if (input_cmd[i] == '"' || input_cmd[i] == '\'')
        {
            while (input_cmd[i] && (input_cmd[i] != '"' || input_cmd[i] != '\''))
                i++;
        }
        if (input_cmd[i] == '|')
        {
            count_pipes = 0;
            while (input_cmd[i] && input_cmd[i] == '|')
            {
                count_pipes++;
                i++;
            }
            if (count_pipes > 2 && count_pipes != 0)
            {
                ft_error_msg(cmd, "syntax error near unexpected token ", '|', 2);
                return (1);
            }
            if (empty_after_symbol(&input_cmd[i]) && count_pipes != 0)
            {
                ft_error_msg(cmd, "unexpected EOF while looking for matching ", '|', 2);
                return (1);
            }
        }
        if (input_cmd[i])
            i++;
    }
    return (0);
}
