/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:30:31 by alphan            #+#    #+#             */
/*   Updated: 2024/07/13 13:25:53 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/new_lexer.h"

void	change_value(t_token *current, t_token_type type)
{
	char	*str;

	str = ft_strjoin(current->value, current->next->value);
	free(current->next->value);
	current->next->value = ft_strdup(str);
	current->next->type = type;
	free(str);
	free(current->value);
	current->value = NULL;
}

void	rm_space(t_token *token)
{
	t_token	*current;
	t_token	*tmp;
	t_token	*prec;

	tmp = token;
	current = token;
	while (current)
	{
		while (current->next && (current->type == SPACE))
		{
			tmp = current->next;
			if (current->value)
				free(current->value);
			free(current);
			prec->next = tmp;
			current = tmp;
		}
		prec = current;
		current = current->next;
	}
}

void	new_lexer(t_token **token, t_envp **envp)
{
	remove_quote(*token, envp);
	if (!token)
		printf("test");
	change_cmd(*token);
	rm_space(*token);
	change_red(*token);
}

void	del_null_value(t_token *token)
{
	t_token	*current;
	t_token	*tmp;
	t_token	*prec;

	tmp = token;
	current = token;
	while (current)
	{
		while (current->next && (!current->value || current->type == SPACE))
		{
			tmp = current->next;
			free(current);
			prec->next = tmp;
			current = tmp;
		}
		prec = current;
		current = current->next;
	}
}
