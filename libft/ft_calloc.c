/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:28:00 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/17 13:59:43 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ret;
	size_t	total_size;

	total_size = count * size;
	if (count == 0 || size == 0)
		return (ft_calloc(1, 1));
	if ((count >= 2147483647 || size >= 2147483647))
		return (NULL);
	ret = (void *)malloc(total_size);
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, total_size);
	return ((void *)(ret));
}
