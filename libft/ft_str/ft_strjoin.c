/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:41:54 by alphan            #+#    #+#             */
/*   Updated: 2023/12/19 15:33:22 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	while (*s1)
	{
		*(ret + i) = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		*(ret + i) = *s2;
		i++;
		s2++;
	}
	*(ret + i) = 0;
	return (ret);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1)
		s1 = ft_calloc(1, 1);
	if (!s1 || !s2)
		return (NULL);
	ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (free(s1), s1 = NULL, free(ret), ret = NULL, NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = 0;
	free(s1);
	s1 = NULL;
	return (ret);
}
