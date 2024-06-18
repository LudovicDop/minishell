/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 21:09:02 by alphan            #+#    #+#             */
/*   Updated: 2023/11/07 15:46:21 by alainphan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if ((src == NULL && dest == NULL) || src == dest)
		return (dest);
	if (dest > src)
	{
		while (i < n)
		{
			*(char *)(dest + (n - i - 1)) = *(char *)(src + (n - i - 1));
			i++;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
