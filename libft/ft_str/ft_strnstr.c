/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:12:32 by alphan            #+#    #+#             */
/*   Updated: 2023/11/07 16:00:03 by alainphan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s1 == s2)
		return ((char *)s2);
	if (!ft_strlen(s2))
		return ((char *)s1);
	while (i < len && *(s1 + i))
	{
		j = 0;
		while (*(s1 + (i + j)) == *(s2 + j) && (i + j) < len && *(s2 + j) && \
			*(s1 + i + j))
			j++;
		if ((*(s2 + j) == 0))
			return ((char *)(s1 + i));
		i++;
	}
	return (NULL);
}
