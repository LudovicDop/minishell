/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:04:02 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/17 12:05:56 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *neddle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*haystack == '\0' && *neddle == '\0')
		return ((char *)(haystack));
	if (*neddle == '\0')
		return ((char *)(haystack));
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (haystack[i + j] == neddle[j] && (i + j) < len)
		{
			j++;
			if (neddle[j] == '\0')
			{
				return ((char *)(haystack + i));
			}
		}
		i++;
	}
	return (NULL);
}
