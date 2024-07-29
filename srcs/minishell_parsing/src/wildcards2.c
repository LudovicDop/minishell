/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <alphan@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:42:14 by alphan            #+#    #+#             */
/*   Updated: 2024/07/28 01:46:42 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wildcards.h"

char	*ft_strchr3(const char *s, int c, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

int	ft_strinstr(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		if (s1[i] == s2[j])
		{
			i++;
			j++;
		}
		i++;
	}
	if (s2[j])
		return (0);
	return (1);
}

int	ft_strcmp2(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (!s1[i])
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp_reverse(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	k = 0;
	while (i > k && s1[k] && s2[k])
	{
		if (s1[i - k - 1] != s2[j - k - 1])
			return ((unsigned char)s1[ft_strlen(s1) - k - 1] != \
			(unsigned char)s2[ft_strlen(s2) - k - 1]);
		k++;
	}
	return (0);
}

int	only_wld(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '*')
			return (0);
		i++;
	}
	return (1);
}
