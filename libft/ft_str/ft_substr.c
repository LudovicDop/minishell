/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <alphan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:54:04 by alphan            #+#    #+#             */
/*   Updated: 2024/07/20 20:56:16 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	lens;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	lens = ft_strlen(s);
	if ((start > lens) || len == 0 || lens == 0)
		return (ft_calloc(1, 1));
	if (len + start > lens)
		len = lens - start;
	ret = (char *)malloc(len + 1);
	if (!ret)
		return (NULL);
	while (i < len)
	{
		*(ret + i) = *(s + start + i);
		i++;
	}
	*(ret + i) = '\0';
	return (ret);
}
