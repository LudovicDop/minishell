/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_freeing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:12:00 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/21 21:05:43 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(void **my_tab)
{
	int	i;

	i = 0;
	if (!my_tab)
		return ;
	while (my_tab[i])
	{
		free(my_tab[i]);
		i++;
	}
	free(my_tab);
}

void	free_everything(t_lexer **token, char *prompt)
{
	if (token)
	{
		free_cmd_list(token);
	}
	if (prompt)
		free(prompt);
}

void	free_cmd_list(t_lexer **token_lst)
{
	t_lexer	*current;
	t_lexer	*to_free;

	current = *token_lst;
	while (current)
	{
		to_free = current;
		current = current->next;
		free(to_free->value);
		free(to_free);
	}
}

void	free_envp(t_envp **envp)
{
	t_envp	*current;
	t_envp	*to_free;

	current = *envp;
	while (current)
	{
		to_free = current;
		current = current->next;
		free(to_free->key);
		free(to_free->value);
		free(to_free);
	}
}

void	free_pwd_lst(t_pwd **pwd)
{
	t_pwd	*current;
	t_pwd	*to_free;

	current = *pwd;
	while (current)
	{
		to_free = current;
		current = current->next;
		free(to_free->node);
		free(to_free);
	}
}
