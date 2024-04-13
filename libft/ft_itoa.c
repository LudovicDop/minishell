/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:18:15 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/24 17:42:43 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	unsigned int	size_of_int(int n)
{
	int				i;
	unsigned int	unsigned_val;

	i = 0;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	unsigned_val = n;
	if (unsigned_val == 0)
		return (1);
	while (unsigned_val > 0)
	{
		unsigned_val = unsigned_val / 10;
		i++;
	}
	return (i);
}

char	*reverse(char *str)
{
	int		i;
	int		len;
	char	tmp;

	i = 0;
	len = 0;
	while (str[len])
		len++;
	len--;
	while (i <= len)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
		i++;
		len--;
	}
	return (str);
}

void	unsigned_next(unsigned int unsigned_n, int is_neg, char *ret)
{
	char	buffer;
	int		i;

	i = 0;
	while (unsigned_n > 0)
	{
		buffer = unsigned_n % 10 + '0';
		ret[i++] = buffer;
		unsigned_n = unsigned_n / 10;
	}
	if (is_neg)
		ret[i++] = '-';
	ret[i] = '\0';
}

char	*ft_itoa(int n)
{
	char			*ret;
	int				is_neg;
	unsigned int	unsigned_n;

	unsigned_n = n;
	is_neg = 0;
	if (n == 0)
		return (ft_strdup("0"));
	ret = ft_calloc(size_of_int(n) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	if (n < 0)
	{
		unsigned_n = n * -1;
		is_neg = 1;
	}
	unsigned_next(unsigned_n, is_neg, ret);
	return (reverse(ret));
}
