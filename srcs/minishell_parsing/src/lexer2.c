/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 22:24:19 by alphan            #+#    #+#             */
/*   Updated: 2024/06/29 11:37:31 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

char	*get_string(char a, char b, char c, int *i)
{
	char	*str;

	str = ft_calloc(4, sizeof(char));
	if (!str)
		return (NULL);
	str[0] = a;
	str[1] = b;
	str[2] = c;
	if (b != 0 || a == '\'' || a == '\"')
		(*i)++;
	return (str);
}

t_token_type	get_token_type2(char*s)
{
	if (!ft_strncmp(s, "||", 2))
		return (OR);
	if (!ft_strncmp(s, "&&", 2))
		return (AND);
	if (!ft_strncmp(s, "|", 1))
		return (PIPE);
	
	if (!ft_strncmp(s, "&", 1))
		return (SEP);
	if (!ft_strncmp(s, "*", 1))
		return (WILDCARD);
	if (!ft_strncmp(s, "~", 1))
		return (WAVE);
	return (CMD);
}

t_token_type	get_token_type(char *s)
{
	if (!s)
		return (CMD);
	if (!ft_strncmp(s, " ", 1) || !ft_strncmp(s, "\t", 1))
		return (SPACE);
	if (!ft_strncmp(s, "'", 1))
		return (QUOTE);
	if (!ft_strncmp(s, "\"", 1))
		return (DOUBLE_QUOTE);
	if (!ft_strncmp(s, "(", 1))
		return (OPEN_PAR);
	if (!ft_strncmp(s, ")", 1))
		return (CLOSE_PAR);
	if (!ft_strncmp(s, ">>", 2))
		return (REDIRECT_APPEND);
	if (!ft_strncmp(s, "<<", 2))
		return (HEREDOC);
	if (!ft_strncmp(s, "<", 1))
		return (REDIRECT_IN);
	if (!ft_strncmp(s, ">", 1))
		return (REDIRECT_OUT);
	
	return (get_token_type2(s));
}

void	push_stack(t_token **token, char *s, t_token_type type)
{
	t_token				*element;
	t_token				*tmp;
	static const int	a[] = {9, 9, 9, 9, 8, 8, 2, 2, 2, 3, 1, 0, 0, 9, 9, 9};
	static int			b;

	element = ft_calloc(sizeof(t_token), 1);
	if (!element)
		return ;
	// *element = (t_token){type, ft_strdup(s), b++, a[type], NULL};
	element->type = type;
	element->value = ft_strdup(s);
	element->pos = b++;
	element->priority = a[type];
	element->next = NULL;
	tmp = *token;
	if (!tmp)
	{
		*token = element;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = element;
}
