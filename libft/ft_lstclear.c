/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:53:30 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/24 15:33:49 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*buffer;
	t_list	*next;

	if (!del)
	{
		return ;
	}
	buffer = *lst;
	next = buffer;
	while (buffer)
	{
		next = buffer->next;
		del(buffer->content);
		free(buffer);
		buffer = next;
	}
	*lst = NULL;
}
