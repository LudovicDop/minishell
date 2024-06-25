/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:28:30 by alphan            #+#    #+#             */
/*   Updated: 2023/11/07 16:03:41 by alainphan        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_rev_char_tab(char *t)
{
	int		i;
	int		size;
	char	tmp;

	i = 0;
	size = ft_strlen(t) - 1;
	while (i < size)
	{
		tmp = t[i];
		t[i] = t[size];
		t[size] = tmp;
		i++;
		size--;
	}
	return (t);
}

static char	*iszero(void)
{
	char	*t;

	t = malloc(2);
	if (!t)
		return (NULL);
	t[0] = '0';
	t[1] = 0;
	return (t);
}

char	*ft_itoa(int n)
{
	int				i;
	char			t[12];
	unsigned int	nb;
	int				tmp;

	i = 0;
	tmp = 0;
	if (n == 0)
		return (iszero());
	nb = n;
	if (n < 0)
	{
		nb = -n;
		tmp = 1;
	}
	while (nb != 0)
	{
		t[i] = nb % 10 + '0';
		nb /= 10;
		i++;
	}
	if (tmp)
		t[i++] = '-';
	t[i] = '\0';
	return (ft_strdup(ft_rev_char_tab(t)));
}
