/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:11:39 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/22 11:46:10 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_;
	const unsigned char	*s2_;
	size_t				i;

	s1_ = (const unsigned char *)s1;
	s2_ = (const unsigned char *)s2;
	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (i < n && s1_[i] == s2_[i] && s1_ && s2_)
	{
		i++;
	}
	if (i < n && s1_[i] != s2_[i])
	{
		return (s1_[i] - s2_[i]);
	}
	return (0);
}
