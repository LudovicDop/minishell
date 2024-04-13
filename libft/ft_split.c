/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:32:53 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/24 17:17:13 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	how_many_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	if (s[0] == '\0')
		return (0);
	if (ft_memchr(s, c, ft_strlen(s)) == NULL)
		return (1);
	while (s[i] == c)
		i++;
	while (i < ft_strlen(s))
	{
		if (s[i] == c)
		{
			j++;
			while (s[i] == c)
				i++;
		}
		i++;
	}
	if (s[ft_strlen(s) - 1] != c)
		return (j + 1);
	return (j);
}

static void	allocate_mem(char const *s, char c, char **ret)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	k = 0;
	j = 0;
	i = 0;
	while (i < ft_strlen(s))
	{
		j = 0;
		while (s[i] != c && s[i])
		{
			j++;
			i++;
		}
		if (j != 0)
		{
			ret[k] = (char *)malloc(sizeof(char) * (j + 1));
			if (!ret[k])
				return ;
			k++;
		}
		i++;
	}
	ret[k] = NULL;
}

static char	**implement_my_table(char const *s, char c, char **ret)
{
	unsigned int	i;
	unsigned int	k;
	unsigned int	j;

	k = 0;
	j = 0;
	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			j = 0;
			while (i < ft_strlen(s) && s[i] != c)
			{
				ret[k][j] = s[i];
				j++;
				i++;
			}
			ret[k][j] = '\0';
			k++;
		}
		i++;
	}
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char			**ret;

	if (!s)
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * (how_many_split(s, c) + 1));
	if (!ret)
		return (NULL);
	allocate_mem(s, c, ret);
	implement_my_table(s, c, ret);
	return (ret);
}
