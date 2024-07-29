/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <alphan@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 00:54:59 by alphan            #+#    #+#             */
/*   Updated: 2024/07/28 01:57:02 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wildcards.h"
#include <dirent.h>

void	pre_wld(char **tmp, struct dirent *entree, t_token **new)
{
	if (tmp[2] && ft_strncmp(tmp[2], "", 2))
	{
		if (tmp[1] && !ft_strncmp(tmp[0], entree->d_name, ft_strlen(tmp[0])) \
		&& !ft_strncmp_reverse(tmp[1], entree->d_name) && \
		ft_strinstr(entree->d_name + ft_strlen(tmp[0]), tmp[2]))
			push_stack(new, entree->d_name, CMD);
		else if (!tmp[1] && ft_strinstr(entree->d_name + ft_strlen(tmp[0]), \
		tmp[2]))
			push_stack(new, entree->d_name, CMD);
	}
	else if (tmp[2] && !ft_strncmp(tmp[2], "", 2) && tmp[1] && \
	!ft_strncmp_reverse(tmp[1], entree->d_name))
		push_stack(new, entree->d_name, CMD);
	else if (!tmp[1] && !ft_strncmp(tmp[0], entree->d_name, ft_strlen(tmp[0])))
		push_stack(new, entree->d_name, CMD);
}

void	middle_wld(char **tmp, struct dirent *entree, t_token **new)
{
	if (tmp[1] && \
	!ft_strncmp_reverse(tmp[1], entree->d_name) && \
	ft_strinstr(entree->d_name, tmp[2]))
		push_stack(new, entree->d_name, CMD);
	else if (!tmp[1] && entree->d_name[0] != '.' && \
	ft_strinstr(entree->d_name, tmp[2]))
		push_stack(new, entree->d_name, CMD);
}

int	only_wld(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '*')
			return (0);
		i++;
	}
	return (1);
}

t_token	*create_wld(char **tmp, t_token **new, t_token *current)
{
	DIR				*dossier;
	struct dirent	*entree;

	dossier = opendir(".");
	if (dossier == NULL)
		return (NULL);
	entree = readdir(dossier);
	while (entree)
	{
		if (tmp[0] && !ft_strcmp2(tmp[0], entree->d_name))
			pre_wld(tmp, entree, new);
		else if (!tmp[0] && tmp[2] && ft_strncmp(tmp[2], "", 2))
			middle_wld(tmp, entree, new);
		else if (only_wld(current->value) || \
		(!tmp[0] && tmp[1] && !ft_strncmp_reverse(entree->d_name, tmp[1])))
		{
			if (entree->d_name[0] != '.')
				push_stack(new, entree->d_name, CMD);
		}
		entree = readdir(dossier);
	}
	if (closedir(dossier) == -1)
		return (NULL);
	return (*new);
}
