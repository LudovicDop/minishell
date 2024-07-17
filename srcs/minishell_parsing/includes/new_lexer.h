/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:31:26 by alphan            #+#    #+#             */
/*   Updated: 2024/07/07 12:53:13 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_LEXER_H
# define NEW_LEXER_H

# include "../includes/lexer.h"

char	*remove_quotes(char *str);
void	remove_fisrt_quote(t_token *token);
void	change_value(t_token *current, t_token_type type);
void	new_lexer(t_token **token);
void	del_null_value(t_token *token);
#endif
