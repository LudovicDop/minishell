/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_value.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:14:28 by alphan            #+#    #+#             */
/*   Updated: 2024/07/18 14:14:29 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANGE_VALUE_H
# define CHANGE_VALUE_H

# include "../includes/lexer.h"

char	*remove_quotes(char *str);
// void	remove_quote(t_token *token);
void	remove_quote(t_token *token, t_envp **envp);
void	change_red(t_token *token);
void	change_cmd(t_token *token);
void	change_for_value(t_token *token, t_envp **envp, char *str);

#endif
