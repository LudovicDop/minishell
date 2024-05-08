/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/05/08 17:50:18 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pre_alloc(t_cmd **cmd, t_tab *glob, char **envp)
{
    for(int i = 0; i < 3; i++)
    {
        cmd[i] = ft_calloc(1, sizeof(t_cmd));
    }
    printf("\n");

    for (int i = 0; i < 3; i++)
    {
        (cmd[i])->arg = ft_calloc(100, sizeof(char*));
        (cmd[i])->arg_redirection = ft_calloc(100, sizeof(char*));
    }
    for (int i = 0; i < 3; i++)
    {
        (*cmd[i]).tab_ref = glob;
    }
    glob->envp = envp;
}


void    add_to_my_lst(t_envp **list, t_envp *new_node)
{
    t_envp *current;

    if (*list == NULL)
    {
        *list = new_node;
        return ;
    }
    current = *list;
    while (current->next)
    {
        current = current->next;
    }
    current->next = new_node;
    
}

void    read_my_list(t_envp *list)
{
    while (list)
    {
        printf("\033[32;1m%s\033[m\033[31;1m%s\033[m\n", list->key, list->value);
        list = list->next;
    }
}

void    free_envp(t_envp **list)
{
    t_envp *current;
    t_envp *to_free;

    current = *list;
    while (current)
    {
        to_free = current;
        current = current->next;
        free(to_free->key);
        free(to_free->value);
        free(to_free);
    }
}
void    init_envp(t_envp **envp_s, char **envp)
{
    t_envp *new_node;
    int i;

    *envp_s = NULL;
    i = 0;
    if (!envp)
        ;
    new_node = *envp_s;
    while (envp[i])
    {
        new_node = malloc(sizeof(t_envp));
        new_node->value = ft_strdup(ft_strchr(envp[i], '='));
        new_node->key = ft_strchr_reverse(envp[i], '=');
        new_node->next = NULL;
        add_to_my_lst(envp_s, new_node);
        i++;
    }
}
/*Command for test : cat fichier.txt |  sed s/Ceci/Anticonstitutionnellement/g | grep Anticons*/
int main(int argc, char **argv, char **envp)
{
    t_cmd **cmd;
    t_tab *glob;
    t_envp *envp_s;


    init_envp(&envp_s, envp);
    read_my_list(envp_s);
    free_envp(&envp_s);
    while (1)
    {
        cmd = malloc(sizeof(t_cmd));
        glob = malloc(sizeof(t_tab));
        ft_signal();
        pre_alloc(cmd, glob, envp);
        get_prompt();
        (*cmd)->tab_ref->tmp = readline("");
        start_parsing((*cmd)->tab_ref->tmp, cmd);
        add_history((*cmd)->tab_ref->tmp);
        execution_main(cmd);
        if (!(*cmd)->tab_ref->tmp)
        {
            free_everything(cmd);
            break;
        }
        free_everything(cmd);
     }
    return (0);
}



