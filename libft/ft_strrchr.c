/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:41:10 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/17 12:42:43 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	s_size;

	s_size = ft_strlen(s);
	while (s_size >= 0)
	{
		if (s[s_size] == (char)c)
		{
			return ((char *)(s + s_size));
		}
		s_size--;
	}
	return (NULL);
}
