/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_freeing_bis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:21:26 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/25 12:25:54 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_minishell_free(t_lexer **token, t_glob **glob)
{
	if (*token)
		free_lexer(*token);
	free((*glob)->prompt);
	free((*glob)->input_cmd);
	(*glob)->input_cmd = NULL;
}

int	ft_exit_minishell(t_glob **glob, t_envp **envp_list)
{
	free_envp(envp_list);
	free((*glob)->prompt);
	free((*glob)->input_cmd);
	free(*glob);
	return (0);
}

void	free_lexer(t_lexer *lex)
{
	t_lexer	*tmp;
	int		i;

	while (lex)
	{
		i = 0;
		tmp = lex;
		while (lex->value[i])
		{
			free(lex->value[i]);
			i++;
		}
		free(lex->value);
		lex = lex->next;
		free(tmp);
	}
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		if (token->value)
			free(token->value);
		token = token->next;
		free(tmp);
	}
}

void	ft_init_glob(t_glob **glob, t_lexer **token, t_envp **envp_list)
{
	(*glob)->root = *token;
	(*glob)->envp = *envp_list;
	(*glob)->id_node = NULL;
}
