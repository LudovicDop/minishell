/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:12:10 by alphan            #+#    #+#             */
/*   Updated: 2024/07/18 14:12:11 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/change_value.h"

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
			change_for_value(current, envp, current->value);
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
			change_for_value(current, envp, current->value);
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
	while (current)
	{
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
			// current->value = ft_strdup(tmp->value);
		}
		else if (current->value[0] == '~')
		{
			tmp = search_envp_key(envp, "HOME");
			free(current->value);
			current->value = ft_strdup(str);
			// free(str);
		}
		current = current->next;
	}
}
void	change_for_value(t_token *token, t_envp **envp, char *str)
{
	t_token	*current;
	int		i;
	t_envp	*tmp;

	current = token;
	while (current)
	{
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
			// current->value = ft_strdup(tmp->value);
		}
		else if (current->value[0] == '~')
		{
			tmp = search_envp_key(envp, "HOME");
			free(current->value);
			current->value = ft_strdup(str);
			// free(str);
		}
		current = current->next;
	}
}

/*
{
	t_token	*current;
	char	*str;
	char	tmp[] = "le chemion du path";
	char	*str2;
	int		i;
	int		j;

	current = token;
	i = 0;
	// remplace $? par le code de retour exit_status
	j = 0;
	while (current)
	{
		if (current->type == CMD && !ft_strncmp(current->value, "$", 1))
		{
			if (!ft_strncmp(current->value, "$?", 2))
			{
				free(current->value);
				current->value = ft_itoa(i);
			}
			else if (!ft_strncmp(current->value, "$$", 2))
			{
				free(current->value);
				current->value = ft_itoa(i);
			}
			else if (!ft_strncmp(current->value, "$PATH", 6))
			{
				free(current->value);
				current->value = ft_strdup("le chemion du path");
			}
		}
		else if (current->type == CMD && !ft_strncmp(current->value, "~", 1))
		{
			// str = ft_strjoin("/Users/", current->value + 1);
			free(current->value);
			// current->value = ft_strdup(str);
			free(str);
		}
		current = current->next;
	}
}
*/
