/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_final.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:37:49 by alphan            #+#    #+#             */
/*   Updated: 2024/07/12 11:37:51 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_TOKEN_FINAL_H
# define CREATE_TOKEN_FINAL_H

# include "../includes/new_lexer.h"

void	push_stack2(t_lexer **token, t_token_type t, char **value);
void	count_value(t_token *c, t_index *a);
void	create_cmd_value(t_lexer **token, t_token **c, t_index a);
void	create_red_value(t_lexer **t, t_token **c, t_index a);
void	create_token(t_token **c, t_lexer **token);

#endif
