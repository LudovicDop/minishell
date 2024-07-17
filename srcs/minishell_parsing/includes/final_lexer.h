/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_lexer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:57:55 by alphan            #+#    #+#             */
/*   Updated: 2024/07/16 02:16:37 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINAL_LEXER_H
# define FINAL_LEXER_H

# include "../includes/create_token_final.h"

void	create_token(t_token **c, t_lexer **token);
void	final_lexer(t_token *t, t_lexer **token);

#endif
