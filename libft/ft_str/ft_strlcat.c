/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:19:35 by alphan            #+#    #+#             */
/*   Updated: 2023/11/07 15:58:57 by alainphan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen(dest);
	k = i;
	j = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (size != 0 && i < size - 1 && src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = 0;
	if (size < ft_strlen(dest))
		return (ft_strlen(src) + size);
	else if (size > ft_strlen(src) && size < ft_strlen(dest))
		return (ft_strlen(src));
	else
		return (k + ft_strlen(src));
}
