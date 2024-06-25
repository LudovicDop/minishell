/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:28:31 by alphan            #+#    #+#             */
/*   Updated: 2023/11/07 15:59:39 by alainphan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*s1;

	i = 0;
	s1 = ft_strdup(s);
	if (!s1)
		return (NULL);
	while (s[i])
	{
		*(s1 + i) = f(i, s[i]);
		i++;
	}
	return (s1);
}
