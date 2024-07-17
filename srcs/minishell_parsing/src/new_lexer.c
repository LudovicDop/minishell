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

void	remove_quote_and_space(t_token *token)
{
	t_token	*current;
	// char	*str;

	current = token;
	while (current)
	{
		// if (current->type == CMD)
		// {
		// 	str = ft_strtrim(current->value, " \t\b\n\v\f\r");
		// 	free(current->value);
		// 	current->value = ft_strdup(str);
		// 	free(str);
		// }
		if (current->type == QUOTE || current->type == DOUBLE_QUOTE)
		{
			current->value = remove_quotes(current->value);
			current->type = CMD;
		}
		current = current->next;
	}
}

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

void	rm_space_or_null(t_token *token)
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
void	change_for_value(t_token *token)
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
		if (current->type == DOUBLE_QUOTE)
		{
			current->value = remove_quotes(current->value);
			while (current->value[i] == ' ' || current->value[i] == '\t')
				i++;
			str2 = ft_substr(current->value, i, ft_strlen(current->value));
			if (!ft_strncmp(str2, "$PATH", 6))
			{
				if (i)
				{
					str = ft_calloc(i + 2, sizeof(char));
					while (j <= i)
					{
						str[j] = ' ';
						j++;
					}
				}
				else
					str = ft_strdup(" ");	
				free(current->value);
				printf("str = '%s'\n", str);
				// current->value = ft_strdup(str);
				current->value = ft_strjoin(str, tmp);
				free(str);
			}
		}
		else if (current->type == CMD && !ft_strncmp(current->value, "$", 1))
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
		current = current->next;
	}
}

void	new_lexer(t_token **token)
{
	//search cmd == envp && do wave for d_quote et cmd 
	// change_for_value(*token);
	remove_quote_and_space(*token);
	change_cmd(*token);
	rm_space_or_null(*token);
	change_red(*token);
	rm_space_or_null(*token);
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
