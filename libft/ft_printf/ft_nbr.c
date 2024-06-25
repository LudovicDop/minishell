/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <alphan@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 00:12:09 by alphan            #+#    #+#             */
/*   Updated: 2023/11/13 22:05:18 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	number(int n)
{
	size_t	len;
	char	*nbr;

	len = 0;
	nbr = ft_itoa(n);
	len = ft_putstr(nbr);
	free(nbr);
	return (len);
}

size_t	pointeur(unsigned long long p)
{
	char	s[22];
	int		i;
	char	*base;
	size_t	len;

	base = "0123456789abcdef";
	i = 0;
	write(1, "0x", 2);
	len = 2;
	if (p == 0)
		return (len += ft_putchar('0'));
	while (p)
	{
		s[i] = base[p % 16];
		p /= 16;
		i++;
	}
	while (i--)
	{
		ft_putchar(s[i]);
		len++;
	}
	return (len);
}

size_t	base(unsigned int p, char c)
{
	char	s[20];
	int		i;
	char	*base;
	size_t	len;

	if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	i = 0;
	len = count(p, 16);
	if (p == 0)
	{
		ft_putchar('0');
		return (1);
	}
	while (p)
	{
		s[i] = base[p % 16];
		p /= 16;
		i++;
	}
	while (i--)
		ft_putchar(s[i]);
	return (len);
}

size_t	count(unsigned long long n, unsigned long long base)
{
	int	len;

	len = 1;
	while (n >= base)
	{
		n /= base;
		len++;
	}
	return (len);
}

size_t	unsigne(unsigned int n)
{
	size_t	len;

	len = count(n, 10);
	if (n > 9)
		unsigne(n / 10);
	ft_putchar(n % 10 + '0');
	return (len);
}
