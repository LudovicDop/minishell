/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <alphan@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:17:38 by alphan            #+#    #+#             */
/*   Updated: 2024/06/18 11:21:44 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../includes/lexer.h"

typedef struct s_node
{
	t_token_type	type;
	char			*value;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

t_node	*parse(t_token *token);
#endif
