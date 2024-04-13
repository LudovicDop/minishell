/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:32:27 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/24 15:32:18 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*src_;
	char		*dest_;

	if (!dest && !src)
		return (NULL);
	src_ = src;
	dest_ = dest;
	i = 0;
	while (i < n)
	{
		dest_[i] = src_[i];
		i++;
	}
	return (dest_);
}
