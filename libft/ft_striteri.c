/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:53:28 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/17 14:54:06 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned char	i;
	unsigned int	len;

	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		f(i, s);
		i++;
		s++;
	}
}
