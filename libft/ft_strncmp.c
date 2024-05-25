/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:48:07 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/24 12:49:25 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	s1_;
	unsigned char	s2_;

	i = 0;
	s1_ = (unsigned char) s1[i];
	s2_ = (unsigned char) s2[i];
	if (n == 0)
		return (0);
	if (s1[i] == '\0' || s2[i] == '\0')
		return (s1_ - s2_);
	while (s1[i] != '\0' && s2[i] != '\0' && i < (n - 1))
	{
		if (s1[i] != s2[i])
		{
			s1_ = (unsigned char) s1[i];
			s2_ = (unsigned char) s2[i];
			return (s1_ - s2_);
		}
		i++;
	}
	s1_ = (unsigned char) s1[i];
	s2_ = (unsigned char) s2[i];
	return (s1_ - s2_);
}
