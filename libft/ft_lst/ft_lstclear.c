/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:12:39 by alphan            #+#    #+#             */
/*   Updated: 2023/11/07 15:37:51 by alainphan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*buffer;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		buffer = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = buffer;
	}
	*lst = NULL;
}
