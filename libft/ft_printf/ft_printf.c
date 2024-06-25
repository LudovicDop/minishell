/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alainphan <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:56:42 by alainphan         #+#    #+#             */
/*   Updated: 2023/11/13 22:05:28 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

size_t	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
	return (i);
}

int	char_ok(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u' \
	|| c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

size_t	conversion(va_list *ap, const char c)
{
	size_t	len;

	len = 0;
	if (c == 'c')
		len += ft_putchar(va_arg(*ap, int));
	else if (c == '%')
		len += ft_putchar('%');
	else if (c == 's')
		len += ft_putstr(va_arg(*ap, char *));
	else if (c == 'd' || c == 'i')
		len += number(va_arg(*ap, int));
	else if (c == 'p')
		len += pointeur(va_arg(*ap, unsigned long long));
	else if (c == 'x' || c == 'X')
		len += base(va_arg(*ap, unsigned int), c);
	else if (c == 'u')
		len += unsigne(va_arg(*ap, unsigned int));
	return (len);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(ap, s);
	while (s[i])
	{
		if (s[i] == '%' && char_ok(s[i +1]))
		{
			len += conversion(&ap, s[i + 1]);
			i++;
		}
		else
			len += ft_putchar(s[i]);
		i++;
	}
	va_end(ap);
	return (len);
}
