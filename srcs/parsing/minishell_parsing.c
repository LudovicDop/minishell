/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:24:09 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/26 00:39:32 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    add_cmd_node(t_cmd *new_node, t_cmd **cmd_lst, t_tab **global, t_envp **envp)
{
    t_cmd *new;
    t_cmd *current;

    new = new_node;
    new->tab_ref = *global;
    new->envp_ref = *envp;
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
    if (!(*new_node)->arg)
        (*new_node)->arg = ft_strdup(input_cmd);
    else
        (*new_node)->arg = ft_strjoin2((*new_node)->arg, input_cmd);
    (*new_node)->arg = ft_strjoin2((*new_node)->arg, " ");
}

void    start_parsing(char *input_cmd, t_cmd **cmd, t_envp **envp)
{
    t_cmd *current_node;
    t_tab *global;
    char **input_cmd_split;
    int i;

    if (!input_cmd || *input_cmd == '\0')
        return ;
    global = ft_calloc(sizeof(t_envp), 1);
    i = 0;
    input_cmd_split = ft_split(input_cmd, ' ');
    if (!input_cmd_split)
        return ;
    current_node = ft_calloc(sizeof(t_cmd), 1);
    if (!current_node)
        return ;
    while (input_cmd_split[i])
    {
        if (input_cmd_split[i][0] == '|')
        {
            i++;
            add_cmd_node(current_node, cmd, &global, envp);
            current_node = ft_calloc(sizeof(t_cmd), 1);
        }
        if (!ft_strcmp(input_cmd_split[i], ">"))
        {
            current_node->any_redirection = true;
            fprintf(stderr, "\033[32;1mRedirection : true!\033[m\n");
            while (input_cmd_split[i] && ft_strcmp(input_cmd_split[i], "|"))
            {
                fprintf(stderr, "\033[31;1mParsing redirection!\033[m\n");
                if (!current_node->arg_redirection)
                    current_node->arg_redirection = ft_strdup(input_cmd_split[i]);
                else
                    current_node->arg_redirection = ft_strjoin(current_node->arg_redirection, input_cmd_split[i]); 
                fprintf(stderr, "\033[31;1m%s\033[m\n", current_node->arg_redirection);
                i++;
            }
            if (!input_cmd_split[i])
            {
                add_cmd_node(current_node, cmd, &global, envp);
                return;
            }
        }
        refill_my_node(input_cmd_split[i], &current_node);
        i++;
    }
    add_cmd_node(current_node, cmd, &global, envp);
    free_tab((void**)input_cmd_split);
}
