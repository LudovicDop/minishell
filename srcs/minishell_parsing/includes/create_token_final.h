/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_final.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:37:49 by alphan            #+#    #+#             */
/*   Updated: 2024/07/16 03:15:07 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_TOKEN_FINAL_H
# define CREATE_TOKEN_FINAL_H

# include "../includes/new_lexer.h"

void			incr_index(t_token *c, t_index *a);
void			count_value(t_token *c, t_index *a);
void			create_value(t_lexer **token, t_token **c, t_token_type type, int i);
t_token_type	search_red_type(t_token **c);
void			create_red_value(t_lexer **t, t_token **c, t_index a);

#endif
