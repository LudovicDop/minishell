/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:24:09 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/25 10:16:16 by ldoppler         ###   ########.fr       */
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

int    check_error(char *input_cmd, t_cmd *cmd)
{
    if (!input_cmd)
        return (0);
    if (check_simple_quotes(input_cmd, cmd))
        return (1);
    if (check_double_quotes(input_cmd, cmd))
        return (1);
    if (check_pipes(input_cmd, cmd))
        return (1);
    if (check_redirection_symbol(input_cmd, cmd))
        return (1);
    return (0);
}
int    start_parsing(char *input_cmd, t_cmd **cmd, t_envp **envp)
{
    t_cmd *current_node;
    t_tab *glob;
    char **input_cmd_split;
    int i;

    if (check_error(input_cmd, *cmd))
        return (1);
    if (!input_cmd || *input_cmd == '\0')
        return (0);
    glob = ft_calloc(sizeof(t_tab), 1);
    i = 0;
    input_cmd_split = ft_split(input_cmd, ' ');
    if (!input_cmd_split)
        return (0);
    current_node = ft_calloc(sizeof(t_cmd), 1);
    if (!current_node)
        return (1);
    while (input_cmd_split[i])
    {
        if (input_cmd_split[i][0] == '|')
        {
            i++;
            add_cmd_node(current_node, cmd, &glob, envp);
            current_node = ft_calloc(sizeof(t_cmd), 1);
        }
        if (!ft_strcmp(input_cmd_split[i], ">"))
        {
            current_node->any_redirection = true;
            while (input_cmd_split[i] && ft_strcmp(input_cmd_split[i], "|"))
            {
                if (!current_node->arg_redirection)
                    current_node->arg_redirection = ft_strdup(input_cmd_split[i]);
                else
                    current_node->arg_redirection = ft_strjoin(current_node->arg_redirection, input_cmd_split[i]); 
                i++;
            }
            if (!input_cmd_split[i])
            {
                add_cmd_node(current_node, cmd, &glob, envp);
                return (0);
            }
        }
        refill_my_node(input_cmd_split[i], &current_node);
        i++;
    }
    add_cmd_node(current_node, cmd, &glob, envp);
    free_tab((void**)input_cmd_split);
    return (0);
}
