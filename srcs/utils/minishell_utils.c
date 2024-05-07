/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:40:26 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/07 14:39:17 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
    int i;
    int s1_lenght;
    int s2_lenght;

    s1_lenght = ft_strlen(s1);
    s2_lenght = ft_strlen(s2);
    i = 0;

    while (i <= s1_lenght && i <= s2_lenght)
    {
        if (s1[i] != s2[i])
        {
            return (s1[i] - s2[i]);
        }
        i++;
    }
    return (0);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*ret;
	size_t	string_size;
	int		i;
	int		j;

	j = 0;
	i = 0;
	string_size = ft_strlen(s1) + ft_strlen(s2);
	ret = malloc(sizeof(char) * (string_size + 1));
	if (ret == NULL)
		return (NULL);
	while (s1[j] != '\0')
	{
		ret[i++] = s1[j++];
	}
	j = 0;
	while (s2[j] != '\0')
	{
		ret[i++] = s2[j++];
	}
	ret[i] = '\0';
    free(s1);
	return (ret);
}

char	*ft_strchr_reverse(char *s1, char c)
{
	int i;
	int j;
	int lenght;
	char *new_string;

	lenght = 0;
	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	while (s1[i++] != '=')
		lenght++;
	printf("i = %d\n", i);
	new_string = malloc(sizeof(char) * lenght + 1);
	i = 0;
	while (s1[i])
	{
		if (i < lenght)
			new_string[j++] = s1[i];
		i++;
	}
	new_string[j] = '\0';
	return (new_string);	
}
