/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:18:10 by alphan            #+#    #+#             */
/*   Updated: 2023/11/07 15:38:56 by alainphan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*buffer;
	t_list	*first;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	first = NULL;
	while (lst)
	{
		content = f(lst->content);
		buffer = ft_lstnew(content);
		if (!buffer)
		{
			del(content);
			free(buffer);
			ft_lstclear(&first, del);
			return (NULL);
		}
		ft_lstadd_back(&first, buffer);
		lst = lst->next;
	}
	return (first);
}
