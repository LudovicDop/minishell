/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:43:06 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/23 18:11:40 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const char	*str_;
	size_t		i;

	str_ = (const char *)str;
	i = 0;
	while (i < n)
	{
		if (str_[i] == (char)c)
			return ((void *)(str + i));
		i++;
	}
	return (0);
}
