/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:24:48 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/24 16:08:38 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	if_n_not_null(int n, int fd)
{
	unsigned int	unsigned_n;
	char			buffer;

	buffer = '\0';
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
	}
	unsigned_n = n;
	if (unsigned_n > 0)
	{
		buffer = unsigned_n % 10 + '0';
		if_n_not_null((unsigned_n / 10), fd);
	}
	if (buffer)
		write(fd, &buffer, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
		write(fd, "0", 1);
	else
		if_n_not_null(n, fd);
}
