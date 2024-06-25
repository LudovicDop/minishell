/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 22:17:10 by alphan            #+#    #+#             */
/*   Updated: 2024/06/23 22:17:12 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/print_test.h"

void	print_token(t_token *token)
{
	static const char	*s[] = {"CMD    ", "SPACE  ", "QUOTE  ", "D_QUOTE", \
	"OP_PAR ", "CL_PAR ", "RED_IN ", "RED_OUT", \
	"RED_APP", "HEREDOC", "PIPE   ", "OR     ", "AND    ", "SEP    ", \
	"WCARD  ", "WAVE   "};

	ft_printf("print_token\n");
	while (token)
	{
		ft_printf("TOKEN TYPE: %s", s[token->type]);
		ft_printf("\t tpos: %d ", token->pos);
		ft_printf("\t priority: %d ", token->priority);
		ft_printf("\t value: [%s]\n", token->value);
		token = token->next;
	}
}

int	execute_tree(t_node *node)
{
	static const char	*s[] = {"CMD", "SPACE", "QUOTE", "DOUBLE_QUOTE", \
	"OPEN_PAR", "CLOSE_PAR", "REDIRECT_IN", "REDIRECT_OUT", \
	"REDIRECT_APPEND", "HEREDOC", "PIPE", "OR", "AND", "SEP", \
	"WILDCARD", "WAVE"};

	if (!node)
		return (0);
	if (node->type)
		ft_printf("%s: %s\n", s[node->type], node->value);
	execute_tree(node->left);
	execute_tree(node->right);
	return (0);
}

void	print_node(t_node *node, int level)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	while (i < level)
	{
		ft_printf(" ");
		i++;
	}
	if (node->type == CMD)
		ft_printf("STRING: %s\n", node->value);
	else
		ft_printf("TOKEN TYPE: %s", node->value);
	print_node(node->left, level + 1);
	print_node(node->right, level + 1);
}
