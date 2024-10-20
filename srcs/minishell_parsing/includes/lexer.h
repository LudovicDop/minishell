/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <alphan@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:31:43 by alphan            #+#    #+#             */
/*   Updated: 2024/07/16 02:07:08 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../../libft/libft.h"
# include "../../../includes/envp.h"

typedef enum e_token_type
{
	CMD,
	SPACE,
	QUOTE,
	DOUBLE_QUOTE,
	OPEN_PAR,
	CLOSE_PAR,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEREDOC,
	PIPE,
	OR,
	AND,
	SEP,
	WILDCARD,
	WAVE,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				pos;
	int				priority;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	t_token_type	type;
	char			**value;
	int				pos;
	int				priority;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_index
{
	int		i;
	int		j;
	int		k;
	int		l;
}	t_index;

t_token			*lexer(char *str);
void			del_null_value(t_token *token);
char			*get_string(char a, char b, char c, int *i);
t_token_type	get_token_type(char *s);
void			push_stack(t_token **token, char *s, t_token_type type);
void			push_stack2(t_lexer **token, t_token_type t, char **value);

#endif
