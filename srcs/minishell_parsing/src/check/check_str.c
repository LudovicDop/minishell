/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:52:02 by alphan            #+#    #+#             */
/*   Updated: 2024/07/30 17:32:44 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/check.h"

int	check_str(char *str)
{
	int	i;
	int	j;

	if (!str)
		return (1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_strchr("\\;", str[i]))
			return (ft_putstr_fd("token invalid\n", 2), 1);
		if (!ft_strchr(" \t\b\n\v\f\r", str[i]))
			j++;
		i++;
	}
	if (j == 0)
		return (1);
	return (0);
}
