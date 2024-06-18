/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:08:34 by alphan            #+#    #+#             */
/*   Updated: 2023/11/07 15:58:22 by alainphan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	if (!len)
	{
		ret = (char *)malloc(1);
		if (!ret)
			return (NULL);
		*ret = 0;
		return (ret);
	}
	ret = (char *)malloc(len + 1);
	if (!ret)
		return (NULL);
	while (i < len)
	{
		*(ret + i) = *(s + i);
		i++;
	}
	*(ret + i) = 0;
	return (ret);
}
