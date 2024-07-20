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
#include <stdlib.h>

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
			// printf("current->value = %s\n", current->value);
			current->value = remove_quotes(current->value);
			change_for_value(current, envp);
			printf("current->value = %s\n", current->value);
			current->type = CMD;
		}
		else if (current->type == QUOTE)
		{
			// printf("current->value = %s\n", current->value);
			current->value = remove_quotes(current->value);
			// printf("current->value = %s\n", current->value);
			current->type = CMD;
		}
		else if (current->type == CMD)
		{
			if (current->value[0] == '$')
				change_for_value(current, envp);
		}
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

void	change_for_value2(t_token *token, t_envp **envp, char *str)
{
	t_token	*current;
	int		i;
	t_envp	*tmp;

	current = token;
	if (!ft_strncmp(current->value, "$?", 3))
	{
		free(current->value);
		current->value = ft_itoa(g_signal);
	}
	else if (!ft_strncmp(current->value, "$$", 3))
	{
		free(current->value);
		current->value = ft_itoa(getpid());
	}
	else if (current->value[0] == '$')
	{
		// printf("current->value = %s\n", current->value);
		tmp = search_envp_key(envp, current->value + 1);
		// printf("tmp->value = %s\n", tmp->value);
		free(current->value);
		if (tmp->value)
			current->value = ft_strdup(tmp->value);
		// free(str);
		// current->value = ft_strdup(tmp->value);
	}
	else if (current->type == WAVE)
	{
		tmp = search_envp_key(envp, "HOME");
		free(current->value);
		if (tmp->value)
			current->value = ft_strdup(tmp->value);
		current->type = CMD;
		// free(str);
	}
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
	while (token->value[a.i])
	{
		// if (token->value[a.i] == '$' && !token->value[a.i + 1])
		// {
		// 	s = ft_strjoin2(s, "$");
		// 	a.i ++;
		// }
		if (token->value[a.i] == '$' && token->value[a.i + 1] == '?')
		{
			s = ft_strjoin2(s, ft_itoa(g_signal));
			a.i += 2;
		}
		else if (token->value[a.i] == '$' && token->value[a.i + 1] == '$')
		{
			s = ft_strjoin2(s, ft_itoa(getpid()));
			a.i += 2;
		}
		else if (token->value[a.i] == '$')
		{
			a.j = a.i + 1;
			while (token->value[a.j] && token->value[a.j] != ' ' && token->value[a.j] != '$')
				a.j++;
			s2 = ft_calloc(a.j - a.i + 1, sizeof(char));
			if (!s2)
				break ;
			a.k = 0;
			while (a.i < a.j)
			{
				s2[a.k] = token->value[a.i];
				a.i++;
				a.k++;
			}
			tmp = search_envp_key(envp, s2 + 1);
			if (tmp && tmp->value)
				s = ft_strjoin2(s, tmp->value);
			else
				s = ft_strjoin2(s, s2);
			free(s2);
			s2 = NULL;
		}
		else if (token->type == DOUBLE_QUOTE)
		{
			a.j = a.i + 1;
			while (token->value[a.j] && token->value[a.j] == ' ' && token->value[a.j] != '$')
				a.j++;
			s2 = ft_calloc(a.j - a.i + 1, sizeof(char));
			if (!s2)
				break ;
			a.k = 0;
			while (a.i < a.j)
			{
				s2[a.k] = token->value[a.i];
				a.i++;
				a.k++;
			}
			s = ft_strjoin2(s, s2);
			free(s2);
			s2 = NULL;
		}
		else
			a.i++;
	}
	if (s)
	{
		free(token->value);
		token->value = ft_strdup(s);
		free(s);
	}
}

void	change_for_value3(t_token *token, t_envp **envp, char *str)
{
	t_token	*current;
	int		i;
	t_envp	*tmp;
	char	*s;

	current = token;
	s = NULL;
	if (!ft_strncmp(current->value, "$?", 3))
	{
		free(current->value);
		current->value = ft_itoa(g_signal);
	}
	else if (!ft_strncmp(current->value, "$$", 3))
	{
		free(current->value);
		current->value = ft_itoa(getpid());
	}
	else if (current->value[0] == '$')
	{
		// printf("current->value = %s\n", current->value);
		tmp = search_envp_key(envp, current->value + 1);
		// printf("tmp->value = %s\n", tmp->value);
		if (tmp->value)
		{
			free(current->value);
			current->value = ft_strdup(tmp->value);
		}
		// free(str);
		// current->value = ft_strdup(tmp->value);
	}
	else if (current->type == WAVE)
	{
		tmp = search_envp_key(envp, "HOME");
		if (tmp->value)
		{
			free(current->value);
			current->value = ft_strdup(tmp->value);
		}
		current->type = CMD;
		// free(str);
	}
}
