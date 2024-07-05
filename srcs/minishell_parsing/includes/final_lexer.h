/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_lexer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:57:55 by alphan            #+#    #+#             */
/*   Updated: 2024/07/04 16:19:01 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINAL_LEXER_H
# define FINAL_LEXER_H

# include "../includes/new_lexer.h"

typedef struct s_lexer
{
	t_token_type	type;
	char			**value;
	int				pos;
	int				priority;
	struct s_lexer	*next;
}	t_lexer;

void	push_stack2(t_lexer **token, t_token_type t, char **value, int j);
void	final_lexer(t_token *t, t_lexer **token);

#endif
