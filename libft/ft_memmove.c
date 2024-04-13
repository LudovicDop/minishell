/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:49:37 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/24 12:30:50 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dest_;
	const char	*src_;

	if (!dest && !src)
		return (NULL);
	dest_ = (char *)dest;
	src_ = (const char *)src;
	i = -1;
	if (dest_ >= (src_ + n) || dest_ < src_)
	{
		while (++i < n)
			dest_[i] = src_[i];
	}
	else
	{
		i = n;
		while (i > 0)
		{
			dest_[i - 1] = src_[i - 1];
			i--;
		}
	}
	return (dest_);
}
