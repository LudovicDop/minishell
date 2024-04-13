/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:02:22 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/24 16:41:22 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;

	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	i;
	size_t			lenght;

	lenght = ft_strlen(s);
	i = 0;
	if (!s)
		return (NULL);
	if (lenght < start || len == 0 || s[0] == '\0')
		return (ft_calloc(1, 1));
	if (len > (lenght + 1))
		len = lenght;
	lenght = calc(s, start, len);
	ret = malloc(sizeof(char) * lenght + 1);
	if (ret == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
