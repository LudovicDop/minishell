/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:24:09 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/15 17:33:40 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    add_cmd_node(t_cmd *new_node, t_cmd **cmd_lst)
{
    t_cmd *new;
    t_cmd *current;

    new = new_node;
    if (!(*cmd_lst))
    {
        (*cmd_lst) = new_node;
        (*cmd_lst)->next = NULL;
        return ;
    }
    current = *cmd_lst;
    while (current->next)
        current = current->next;
    current->next = new;
    return ;
}
void    refill_my_node(char *input_cmd, t_cmd **new_node)
{
    (*new_node)->arg = ft_strjoin((*new_node)->arg, input_cmd);
    (*new_node)->arg = ft_strjoin((*new_node)->arg, " ");
    printf("\033[36;1m%s\033[m\n", (*new_node)->arg);
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
        //printf("\033[36;1m%s\033[m\n", input_cmd_split[i]);
        if (input_cmd_split[i][0] == '|')
        {
            i++;
            printf("\033[31;1mAdding a node!\033[m\n");
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
    add_cmd_node(current_node, cmd);
}
