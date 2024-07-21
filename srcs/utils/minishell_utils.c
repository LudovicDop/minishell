/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:40:26 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/21 19:37:40 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	s1_lenght;
	int	s2_lenght;

	s1_lenght = ft_strlen(s1);
	s2_lenght = ft_strlen(s2);
	i = 0;
	while (i < s1_lenght && i < s2_lenght)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (s1[i] - s2[i]);
}

char	*ft_strchr_reverse(char *s1, char c)
{
	int		i;
	int		j;
	int		lenght;
	char	*new_string;
	
	lenght = 0;
	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	while (s1[i++] != c)
		lenght++;
	new_string = malloc(sizeof(char) * lenght + 1);
	i = 0;
	while (s1[i])
	{
		if (i < lenght)
			new_string[j++] = s1[i];
		i++;
	}
	new_string[j] = '\0';
	return (new_string);
}

char	*ft_strchr2(const char *s, int c)
{
	int				i;
	unsigned char	*ret;

	ret = (unsigned char *)s;
	i = 0;
	while (ret[i] != '\0' && ret[i] != (char)c)
	{
		i++;
	}
	if (ret[i] == (char)c)
	{
		return ((char *)(ret + i) + 1);
	}
	return (0);
}
