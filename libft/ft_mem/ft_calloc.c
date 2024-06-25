/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:36:12 by alphan            #+#    #+#             */
/*   Updated: 2023/12/19 15:28:25 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	temp;

	temp = nmemb * size;
	if ((int)nmemb < 0 || (int)size < 0)
		return (0);
	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(0);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if (temp / nmemb != size)
		return (0);
	ptr = (void *)malloc(temp);
	if (!ptr)
		return (0);
	ft_bzero(ptr, temp);
	return (ptr);
}
