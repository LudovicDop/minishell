/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <alphan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:10 by alphan            #+#    #+#             */
/*   Updated: 2024/07/20 21:05:21 by alphan           ###   ########.fr       */
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

void	change_for_value(t_token *token, t_envp **envp)
{
	t_envp	*tmp;
	t_index	a;
	char	*s;
	char	*s2;

	a = (t_index){0, 0, 0};
	s = NULL;
	s2 = NULL;
	tmp = NULL;
	if (token->type == WAVE)
	{
		tmp = search_envp_key(envp, "HOME");
		if (tmp && tmp->value)
		{
			free(token->value);
			token->value = ft_strdup(tmp->value);
		}
		token->type = CMD;
	}
	while (token->value[a.i])
	{
		if (token->value[a.i] == '$' && token->value[a.i + 1] == '?')
			give_value(&s, &a, g_signal);
		else if (token->value[a.i] == '$' && token->value[a.i + 1] == '$')
			give_value(&s, &a, getpid());
		else if (token->value[a.i])
		{
			a.j = a.i + 1;
			while (token->value[a.j] && token->value[a.j] != ' ' && token->value[a.j] != '$')
				a.j++;
			s = init_value(token, &a, envp, &s);
		}
		else if (token->type == DOUBLE_QUOTE)
		{
			a.j = a.i + 1;
			while (token->value[a.j] && token->value[a.j] == ' ' && token->value[a.j] != '$')
				a.j++;
			s = init_value(token, &a, envp, &s);
		}
	}
	if (s)
	{
		free(token->value);
		token->value = ft_strdup(s);
		free(s);
	}
}
