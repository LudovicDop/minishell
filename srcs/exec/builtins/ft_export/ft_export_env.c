/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:17:12 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/09 22:57:44 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_sort(t_envp **envp)
{
    t_envp *current;
    int i;
    int current_val;
    int max_val;

    i = 0;
    current_val = 0;
    current = *envp;
    max_val = current->key[0];
    if (!current)
        return (0);
    while (current)
    {
        current_val = current->key[0];
        printf("val : %d (%s)<= max : %d (%c)\n", current_val, current->key, max_val, max_val);
        if (current_val < max_val)
        {
            printf("\033[31;1mError\033[m\n");
            return (1);
        }
        else
        {
            max_val = current->key[0];
        }
        current = current->next;
    }
    printf("\033[32;1mSort!\033[m\n");
    return (0);
}

void    ft_swap(t_envp **node, t_envp ** node2)
{
    char *tmp_value;
    char *tmp_key;

    tmp_value = ft_strdup((*node)->value);
    tmp_key = ft_strdup((*node)->key);
    free((*node)->value);
    free((*node)->key);
    // printf("\033[31;1mnode1 : %s && node2 : %s\033[m\n", (*node)->value, (*node2)->value);
    (*node)->value = (*node2)->value;
    (*node)->key = (*node2)->key;
    (*node2)->value = tmp_value;
    (*node2)->key = tmp_key;
    printf("\033[32;1mnode1 : %s && node2 : %s\033[m\n", (*node)->value, (*node2)->value);
}

void   sort_list(t_envp **envp)
{
    t_envp *buffer;
    t_envp *first;

    buffer = *envp;
    first = buffer;
    while (is_sort(&first))
    {
        if (buffer->next && (buffer->value[0] > buffer->next->value[0]))
        {
            ft_swap(&buffer, &buffer->next);
        }
        if (!buffer->next)
        {
            printf("\033[32;1mReset\033[m\n");
            buffer = first;
        }
        else
        {
             buffer = buffer->next;
        }
    }
    return ;
}
void    print_env_export(t_envp **envp)
{
    t_envp *tmp;

    if (!envp)
        return ;
    tmp = *envp;
    sort_list(&tmp);
    while (tmp)
    {
        printf("%s=%s\n", tmp->key, tmp->value);
        tmp = tmp->next;
    }
}