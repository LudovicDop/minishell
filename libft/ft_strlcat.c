/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:49:54 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/20 14:52:22 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			i;
	size_t			j;
	size_t			lenght_dst;

	lenght_dst = ft_strlen(dst);
	j = 0;
	i = ft_strlen(dst);
	if (dstsize == 0)
		return (ft_strlen(src));
	if (i >= dstsize)
		return (ft_strlen(src) + dstsize);
	while (src[j] && i < dstsize - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	if (ft_strlen(src) + ft_strlen(dst) > dstsize)
		return (ft_strlen(src) + lenght_dst);
	if (ft_strlen(src) > dstsize)
		return (ft_strlen(src) + lenght_dst);
	if (ft_strlen(dst) >= dstsize)
		return (ft_strlen(dst) + ft_strlen(src));
	return (i);
}
