/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:41:48 by alphan            #+#    #+#             */
/*   Updated: 2024/06/23 14:41:55 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_H
# define CHECK_H

# include "../includes/parser.h"

int	check_quotes(char *input_cmd);
int	check_op(t_token *token);
int	check_par(char *input_cmd);
int	check_token_par(t_token *token);
#endif
