/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:24:09 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/13 17:04:14 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    add_cmd_node(t_cmd *new_node, t_cmd **cmd_lst)
{
    if (!(*cmd_lst))
    {
        (*cmd_lst) = new_node;
        (*cmd_lst)->next = NULL;
        return ;
    }
    while ((*cmd_lst))
    {
        (*cmd_lst) = (*cmd_lst)->next;
    }
    (*cmd_lst) = new_node;
    (*cmd_lst)->next = NULL;
    return ;
}
void    refill_my_node(char *input_cmd, t_cmd **new_node)
{
    // if (!input_cmd)
    //     return ;
    // if (!ft_strcmp(input_cmd, ">"))
    // {
    //     (*new_node)->any_redirection = true;
    //     (*new_node)->arg_redirection = 
    // }
}

void    start_parsing(char *input_cmd, t_cmd **cmd)
{
    t_cmd *current_node;
    char **input_cmd_split;
    int i;

    if (!input_cmd || *input_cmd == '\0')
        return ;
    i = 0;
    input_cmd_split = ft_split(input_cmd, ' ');
    if (!input_cmd_split)
        return ;
    current_node = ft_calloc(sizeof(t_cmd), 1);
    if (!current_node)
        return ;
    while (input_cmd_split[i])
    {
        printf("\033[36;1m%s\033[m\n", input_cmd_split[i]);
        if (input_cmd_split[i][0] == '|')
        {
            add_cmd_node(current_node, cmd);
            current_node = ft_calloc(sizeof(t_cmd), 1);
        }
        if (!ft_strcmp(input_cmd_split[i], ">"))
        {
            printf("\033[32;1mRedirection : true!\033[m\n");
            current_node->any_redirection = true;
            while (input_cmd_split[i] && ft_strcmp(input_cmd_split[i], "|"))
            {
                printf("\033[31;1m%s\033[m\n", input_cmd_split[i]);
                current_node->arg_redirection = ft_strjoin(current_node->arg_redirection, input_cmd_split[i]); 
                i++;
            }
            if (!input_cmd_split[i])
                return;
        }
        refill_my_node(input_cmd_split[i], &current_node);
        i++;
    }
}
