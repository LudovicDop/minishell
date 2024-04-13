/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:23:50 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/21 18:44:06 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set_present(char const *set, char const *s, size_t i)
{
	size_t	j;

	j = 0;
	while (set[j])
	{
		if (set[j] == s[i])
		{
			return (1);
		}
		j++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*ret;

	len = ft_strlen(s);
	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (is_set_present(set, s, i) == 1 && i < ft_strlen(s))
		i++;
	if (i == ft_strlen(s))
		return (ft_calloc(1, 1));
	while (is_set_present(set, s, (len) - 1) == 1 && len > 0)
		len--;
	if (len == 0 || len == i)
		return (ft_calloc(1, 1));
	ret = malloc(sizeof(char) * (len - i) + 1);
	if (!ret)
		return (NULL);
	while (i < len && s[i] != '\0')
		ret[j++] = s[i++];
	ret[j] = '\0';
	return (ret);
}
