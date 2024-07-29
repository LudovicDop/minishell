/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:40:00 by alphan            #+#    #+#             */
/*   Updated: 2024/07/28 01:50:39 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wildcards.h"

void	init_tmp2(t_token *current, char **tmp, t_index *a)
{
	if (current->value[a->i] == '*')
		a->i++;
	a->k = a->i;
	while (current->value[a->i] && current->value[a->i] != '*')
		a->i++;
	tmp[3] = ft_substr(current->value, a->k, a->i - a->k);
	if (!tmp[3])
		return ;
	tmp[2] = ft_strjoin2(tmp[2], tmp[3]);
	free(tmp[3]);
	a->k = a->i;
}

void	init_tmp(t_token	*current, char **tmp)
{
	t_index	a;

	a = (t_index){0, 0, 0, 0};
	while (current->value[a.i] != '*')
		a.i++;
	if (a.i > 0)
		tmp[0] = ft_substr(current->value, 0, a.i);
	while (current->value[ft_strlen(current->value) - a.j - 1] != '*')
		a.j++;
	if (a.j > 0)
		tmp[1] = ft_substr(current->value, \
		ft_strlen(current->value) - a.j, a.j);
	a.k = a.i;
	while (current->value[a.i] && a.i < \
		(int)ft_strlen(current->value) - a.j - 1)
		init_tmp2(current, tmp, &a);
}

t_token	*do_wld(t_token *token)
{
	char			*tmp[4];
	t_token			*current;
	t_token			*new;

	current = token;
	new = NULL;
	current->type = CMD;
	tmp[0] = NULL;
	tmp[1] = NULL;
	tmp[2] = ft_strdup("");
	if (!tmp[2])
		return (NULL);
	tmp[3] = NULL;
	init_tmp(current, tmp);
	new = create_wld(tmp, &new, current);
	if (tmp[0])
		free(tmp[0]);
	if (tmp[1])
		free(tmp[1]);
	if (tmp[2])
		free(tmp[2]);
	return (new);
}

void	is_wld(t_token **token)
{
	t_token	*current;
	t_token	*tmp;
	t_token	*next;

	current = *token;
	while (current)
	{
		if (current && current->next && current->next->type == WILDCARD)
		{
			tmp = do_wld(current->next);
			if (tmp)
			{
				next = NULL;
				next = current->next->next;
				free(current->next->value);
				free(current->next);
				current->next = tmp;
				while (current->next)
					current = current->next;
				current->next = next;
			}
		}
		else
			current = current->next;
	}
}
