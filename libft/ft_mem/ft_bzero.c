/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:34:22 by alphan            #+#    #+#             */
/*   Updated: 2023/11/07 15:45:25 by alainphan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = n;
	while (i > 0)
	{
		*(char *)s = 0;
		i--;
		s++;
	}
	return ;
}