/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_value2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:54:13 by alphan            #+#    #+#             */
/*   Updated: 2024/07/21 15:54:14 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/change_value.h"
#include "envp.h"

char	*remove_quotes(char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 1;
	j = 0;
	s = ft_calloc(ft_strlen(str), sizeof(char));
	while (str[i])
	{
		s[j] = str[i];
		j++;
		i++;
	}
	s[j] = '\0';
	free(str);
	return (s);
}

void	remove_quote(t_token *token, t_envp **envp)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == DOUBLE_QUOTE)
		{
			current->value = remove_quotes(current->value);
			change_for_value(current, envp);
			current->type = CMD;
		}
		else if (current->type == QUOTE)
		{
			current->value = remove_quotes(current->value);
			current->type = CMD;
		}
		else if (current->type == CMD)
			change_for_value(current, envp);
		else if (current->type == WAVE)
			change_for_value(current, envp);
		current = current->next;
	}
}

void	change_red(t_token *token)
{
	t_token	*current;
	t_token	*tmp;

	tmp = token;
	current = token;
	while (current)
	{
		if (current->next && (current->type == REDIRECT_OUT || \
			current->type == REDIRECT_IN || current->type == REDIRECT_APPEND || \
			current->type == HEREDOC))
		{
			tmp = current->next->next;
			free(current->value);
			current->value = ft_strdup(current->next->value);
			free(current->next->value);
			free(current->next);
			current->next = tmp;
		}
		current = current->next;
	}
}

void	change_cmd(t_token *token)
{
	t_token	*current;
	t_token	*tmp;
	char	*str;

	current = token;
	while (current)
	{
		if (current->next && current->type == CMD && current->next->type == CMD)
		{
			str = ft_strjoin(current->value, current->next->value);
			tmp = current->next->next;
			free(current->value);
			current->value = ft_strdup(str);
			free(current->next->value);
			free(current->next);
			free(str);
			current->next = tmp;
		}
		else
			current = current->next;
	}
}

void	change_wave(t_token *token, t_envp **envp)
{
	t_envp	*tmp;

	tmp = search_envp_key(envp, "HOME");
	if (tmp && tmp->value)
	{
		free(token->value);
		token->value = ft_strdup(tmp->value);
	}
	token->type = CMD;
}
