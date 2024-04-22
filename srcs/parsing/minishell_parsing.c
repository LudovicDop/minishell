/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:24:09 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/04/19 10:44:30 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



// void    init_cmd(t_cmd *cmd, char *string_cmd, char **envp)
// {
//     int i;

//     i = 0;
//     /*Skipping the space and tab*/
//     while ((string_cmd[i] == ' ' || string_cmd[i] == '\t') && string_cmd[i])
//         i++;
//     while (string_cmd[i])
//     {
//         if (string_cmd[i] != ' ' || string_cmd[i] != '\t')
//         {
//             cmd->arg[][] = ft_strjoin(cmd, string_cmd[i]);
//         }
//         i++;
//     }
// }