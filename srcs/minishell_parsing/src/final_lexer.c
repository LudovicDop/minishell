/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:57:38 by alphan            #+#    #+#             */
/*   Updated: 2024/07/05 15:09:35 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/final_lexer.h"

void	push_stack2(t_lexer **token, t_token_type t, char **value)
{
	t_lexer				*element;
	t_lexer				*tmp;
	static const int	a[] = {9, 9, 9, 9, 8, 8, 2, 2, 2, 3, 1, 0, 0, 9, 9, 9};
	static int			b;
	int					i;

	(void)i;
	element = ft_calloc(sizeof(t_token), 1);
	if (!element)
		return ;
	*element = (t_lexer){t, value, b++, a[t], NULL};
	tmp = *token;
	if (!tmp)
	{
		*token = element;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = element;
}

void	final_lexer(t_token *t, t_lexer **token)
{
	t_token	*current;
	t_token	*tmp;
	t_index	a;
	char	**value;

	current = t;
	*token = NULL;
	while (current)
	{
		a = (t_index){0, 0, 0};
		if (!current->next && current->type == CMD)
			a.i++;
		if (!current->next && (current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND))
			a.j++;
		if (current->next && (current->type == CMD || \
			current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND))
		{
			tmp = current;
			while (current->next && (current->type == CMD || \
				current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND))
			{
				if (current->type == CMD)
					a.i++;
				if (current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND)
					a.j++;
				current = current->next;
			}
			if (!current->next && (current->type == CMD || \
				current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND))
			{
				if (current->type == CMD)
					a.i++;
				if (current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND)
					a.j++;
				current = current->next;
			}
			if (a.i)
			{
				a.k = 0;
				current = tmp;
				value = ft_calloc(sizeof(char *), a.i + 1);
				if (!value)
					return ;
				while (current->next && (current->type == CMD || \
					current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND))
				{
					if (current->type == CMD)
						value[a.k++] = current->value;
					current = current->next;
				}
				if (!current->next && (current->type == CMD || \
					current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND))
				{
					if (current->type == CMD)
						value[a.k++] = current->value;
					current = current->next;
				}
				// print_value(value, "CMD", current);
				push_stack2(token, CMD, value);
				// free(value);
			}
			if (a.j)
			{
				a.k = 0;
				current = tmp;
				value = ft_calloc(sizeof(char *), a.j + 1);
				while (current->next && (current->type == CMD || \
					current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND))
				{
					if (current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND)
					{
						value[a.k++] = current->value;
						tmp->type = current->type;
					}
					current = current->next;
				}
				if (!current->next && (current->type == CMD || \
					current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND))
				{
					if (current->type == REDIRECT_OUT || current->type == REDIRECT_APPEND)
					{
						value[a.k++] = current->value;
						tmp->type = current->type;
					}
					current = current->next;
				}
				// print_value(value, "RED", current);
				push_stack2(token, tmp->type, value);
				// free(value);
			}
		}
		else
		{
			a.k = 0;
			value = ft_calloc(sizeof(char *), 2);
				value[a.k] = current->value;
			// print_value(value, NULL, current);
			push_stack2(token, current->type, value);
			// free(value);
			current = current->next;
		}
	}
}
