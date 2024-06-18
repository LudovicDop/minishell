/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:22:41 by alphan            #+#    #+#             */
/*   Updated: 2023/11/07 15:58:02 by alainphan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	*freet(char	**s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		s[i] = 0;
		i++;
	}
	free(s);
	return (NULL);
}

static int	count_word(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	**part(char const *s, char c)
{
	char	**t;
	int		i;
	int		j;
	int		temp;

	i = 0;
	j = 0;
	temp = 0;
	t = (char **)ft_calloc(count_word(s, c) + 1, sizeof(char *));
	if (!t)
		return (NULL);
	while (j < count_word(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		temp = i;
		while (s[i] && s[i] != c)
			i++;
		t[j] = ft_substr(s, temp, i - temp);
		if (!t[j])
			return (freet(t));
		j++;
	}
	t[j] = NULL;
	return (t);
}

char	**ft_split(char const *s, char c)
{
	char	**t;

	if (!s)
		return (NULL);
	t = part(s, c);
	return (t);
}
