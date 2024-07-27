/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:31:26 by alphan            #+#    #+#             */
/*   Updated: 2024/07/28 01:08:03 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_LEXER_H
# define NEW_LEXER_H

# include "../includes/wildcards.h"

void	change_value(t_token *current, t_token_type type);
void	new_lexer(t_token **token, t_envp **envp);
void	del_null_value(t_token *token);
#endif
