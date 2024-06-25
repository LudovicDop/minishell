/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:31:38 by alphan            #+#    #+#             */
/*   Updated: 2024/06/25 17:46:35 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

void	tokenize_substr(char *str, t_token **token, t_index *a, char *tmp)
{
	char	*tmp2;

	while (str[a->i + a->j] && !ft_strchr(tmp, str[a->i + a->j]))
		a->j++;
	if (tmp[0] == '\'' || tmp[0] == '\"')
		tmp2 = ft_substr(str, a->i, a->j + 1);
	else
		tmp2 = ft_substr(str, a->i, a->j);
	if (!tmp2)
		return ;
	if (tmp[0] == '\'' || tmp[0] == '\"')
	{
		push_stack(token, tmp2, get_token_type(tmp2));
		a->i += a->j;
	}
	else
	{
		push_stack(token, tmp2, CMD);
		a->i += a->j - 1;
	}
	free(tmp2);
}

void	tokenize(char *str, t_token **token, t_index *a, char c)
{
	char	*tmp;

	tmp = get_string(str[(a->i)], c, 0, (&a->k));
	if (tmp[0] == '\'' || tmp[0] == '\"')
	{
		free(tmp);
		tmp = get_string(str[(a->i)], c, 0, (&a->j));
		tokenize_substr(str, token, a, tmp);
	}
	else
	{
		free(tmp);
		if (!ft_isprint(str[a->i]))
			tmp = get_string(' ', c, 0, (&a->k));
		else
			tmp = get_string(str[(a->i)], c, 0, (&a->i));
		push_stack(token, tmp, get_token_type(tmp));
	}
	free(tmp);
}

t_token	*lexer(char *str)
{
	t_token	*token;
	t_index	a;

	a = (t_index){0, 0, 0};
	token = NULL;
	while (str[a.i])
	{
		a.j = 0;
		if (ft_strchr("|&<>", str[a.i]) && str[a.i + 1] == str[a.i])
			tokenize(str, &token, &a, str[a.i]);
		else if (ft_strchr("|<>&()~ \t*", str[a.i]) || !ft_isprint(str[a.i]))
			tokenize(str, &token, &a, 0);
		else if (str[a.i + a.j] == '\'' || str[a.i + a.j] == '\"')
			tokenize(str, &token, &a, 0);
		else
			tokenize_substr(str, &token, &a, "*\"'|&<>()~");
		a.i++;
	}
	return (token);
}
