/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:58:31 by ldoppler          #+#    #+#             */
/*   Updated: 2023/10/16 17:27:43 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	ret;
	int	i;
	int	is_neg;

	is_neg = 1;
	i = 0;
	ret = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			is_neg = is_neg * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = (ret * 10) + str[i] - '0';
		i++;
	}
	return (ret * is_neg);
}
