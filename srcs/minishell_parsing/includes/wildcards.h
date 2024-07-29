/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:41:13 by alphan            #+#    #+#             */
/*   Updated: 2024/07/28 00:56:50 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H

# include "../includes/change_value.h"

char	*ft_strchr3(const char *s, int c, int end);
int		ft_strinstr(const char *s1, const char *s2);
int		ft_strcmp2(const char *s1, const char *s2);
int		ft_strncmp_reverse(const char *s1, const char *s2);
t_token	*do_wld(t_token *token);
void	is_wld(t_token **current);
t_token	*create_wld(char **tmp, t_token **new, t_token *current);

#endif
