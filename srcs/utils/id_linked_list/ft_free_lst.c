/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:51:34 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/15 12:57:42 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_free_id_list(t_id **my_list)
{
    t_id *current;
    t_id *to_free;

    to_free = NULL;
    current = *my_list;
    while (current)
    {
        to_free = current;
        current = current->next;
        free(to_free);
    }
    return ;
}