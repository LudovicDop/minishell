/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:10 by alphan            #+#    #+#             */
/*   Updated: 2024/07/21 22:39:05 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/change_value.h"

char	*init_value(t_token	*token, t_index *a, t_envp **envp, char **s)
{
	char	*s2;
	t_envp	*tmp;

	s2 = ft_calloc(a->j - a->i + 1, sizeof(char));
	if (!s2)
		return (NULL);
	a->k = 0;
	while (a->i < a->j)
	{
		s2[a->k] = token->value[a->i];
		a->i++;
		a->k++;
	}
	tmp = search_envp_key(envp, s2 + 1);
	if (tmp && tmp->value && s2[0] == '$')
		*s = ft_strjoin2(*s, tmp->value);
	else
		*s = ft_strjoin2(*s, s2);
	free(s2);
	s2 = NULL;
	return (*s);
}

char	*give_value(char **s, t_index *a, int i)
{
	char	*s2;

	s2 = ft_itoa(i);
	if (!s2)
		return (NULL);
	*s = ft_strjoin2(*s, s2);
	free(s2);
	a->i += 2;
	return (*s);
}

void	replace_val(t_token	*token, t_envp **envp, t_index *a, char **s)
{
	if (token->value[a->i] == '$' && token->value[a->i + 1] == '?')
		give_value(s, a, g_signal);
	else if (token->value[a->i] == '$' && token->value[a->i + 1] == '$')
		give_value(s, a, getpid());
	else if (token->value[a->i])
	{
		a->j = a->i + 1;
		while (token->value[a->j] && token->value[a->j] != ' ' && \
			token->value[a->j] != '$')
			a->j++;
		*s = init_value(token, a, envp, s);
	}
	else if (token->type == DOUBLE_QUOTE)
	{
		a->j = a->i + 1;
		while (token->value[a->j] && token->value[a->j] != '$')
			a->j++;
		*s = init_value(token, a, envp, s);
	}
}

void	change_for_value(t_token *token, t_envp **envp)
{
	t_index	a;
	char	*s;

	a = (t_index){0, 0, 0, 0};
	s = NULL;
	if (token->type == WAVE)
		change_wave(token, envp);
	while (token->value[a.i])
		replace_val(token, envp, &a, &s);
	if (s)
	{
		free(token->value);
		token->value = ft_strdup(s);
		free(s);
	}
}
