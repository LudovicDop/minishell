/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_lexer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:57:55 by alphan            #+#    #+#             */
/*   Updated: 2024/07/08 15:27:03 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINAL_LEXER_H
# define FINAL_LEXER_H

# include "../includes/create_token_final.h"

typedef struct s_glob
{
	int	fd_out_old;
	int	fd_int_old;
}	t_glob;

void	final_lexer(t_token *t, t_lexer **token);

#endif
