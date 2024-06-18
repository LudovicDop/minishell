/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:30:36 by alphan            #+#    #+#             */
/*   Updated: 2023/11/07 15:37:18 by alainphan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ancre;

	ancre = *lst;
	if (!ancre)
	{
		(*lst) = new;
		return ;
	}
	while (ancre->next)
		ancre = ancre->next;
	ancre->next = new;
}
