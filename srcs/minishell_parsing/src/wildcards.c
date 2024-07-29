/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:40:00 by alphan            #+#    #+#             */
/*   Updated: 2024/07/30 01:23:33 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wildcards.h"

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

void	free_token2(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
}

void	is_wld2(t_token *current, t_token *tmp)
{
	t_token	*next;

	next = NULL;
	next = current->next->next;
	free(current->next->value);
	free(current->next);
	current->next = tmp;
	while (current->next)
		current = current->next;
	current->next = next;
}

void	is_wld3(t_token **current, t_token *tmp)
{
	if (ft_strchr((*current)->next->value, '*'))
	{
		tmp = do_wld((*current)->next);
		if (tmp && !tmp->next)
			is_wld2(*current, tmp);
		else
		{
			free_token2(tmp);
			(*current)->next->type = REDIRECT_IN;
			*current = (*current)->next;
		}
	}
}

void	is_wld(t_token **token)
{
	t_token	*current;
	t_token	*tmp;

	current = *token;
	while (current)
	{
		if (current && current->next && current->next->type == WILDCARD)
		{
			tmp = do_wld(current->next);
			if (tmp)
				is_wld2(current, tmp);
			else
				free_token2(tmp);
		}
		else if (current && current->next && \
		(current->next->type == REDIRECT_OUT || \
		current->next->type == REDIRECT_IN || \
		current->next->type == REDIRECT_APPEND) && \
		ft_strchr(current->next->value, '*'))
			is_wld3(&current, tmp);
		else
			current = current->next;
	}
}
