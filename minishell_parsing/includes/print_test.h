/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 22:18:15 by alphan            #+#    #+#             */
/*   Updated: 2024/06/23 22:18:17 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_TEST_H
# define PRINT_TEST_H

# include "../includes/check.h"

void	print_token(t_token *token);
int		execute_tree(t_node *node);
void	print_node(t_node *node, int level);

#endif
