/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alphan <alphan@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:31:46 by alphan            #+#    #+#             */
/*   Updated: 2024/07/16 04:20:10 by alphan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/print_test.h"

void	free_token(t_token *token)
{
	t_token	*tmp;
	while (token)
	{
		tmp = token;
		if (token->value)
			free(token->value);
		token = token->next;
		free(tmp);
	}
}

void	free_lexer(t_lexer *lex)
{
	t_lexer	*tmp;
	int		i;

	while (lex)
	{
		i = 0;
		tmp = lex;
		while (lex->value[i])
		{
			free(lex->value[i]);
			i++;
		}
		free(lex->value);
		lex = lex->next;
		free(tmp);
	}
}

void	free_node(t_node *node)
{
	if (node)
	{
		free_node(node->left);
		free_node(node->right);
		free(node->value);
		free(node);
	}
}

int	main(int ac, char **av)
{
	int		fd;
	char	*str;
	t_token	*token;
	t_lexer	*lex;
	// t_node	*node;

	if (ac != 2)
	{
		ft_printf("Error arguments\n");
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error open file\n");
		exit(1);
	}
	str = get_next_line(fd);
	token = NULL;
	printf("str = %s\n", str);
	while (1)
	{
	if (str && !check_str(str) && !check_quotes(str) && !check_par(str))
	{
		token = lexer(str);
		print_token(token);
		if (token && !check_op(token) && !check_red(token) && !check_token_par(token))
		{
			new_lexer(&token);
			print_token(token);
			if (token)
			{
				final_lexer(token, &lex);
				print_lexer(lex);
				free_lexer(lex);
			}
		}
		free_token(token);
	}
	free(str);
	while ((str = get_next_line(fd)))
		free(str);
	// check_quotes(str);
	// check_par(str);
	// token = lexer(str);
	// print_token(token);
	// printf("ok\n");
	// check_op(token);
	// check_red(token);
	// check_token_par(token);
	// printf("ok\n");
	// new_lexer(&token);
	// print_token(token);
	// printf("ok\n");
	// final_lexer(token, &lex);
	// print_lexer(lex);
	// node = parse(token);
	// print_node(node, 0);
	// free(str);
	// while ((str = get_next_line(fd)))
	// 	free(str);
	// free_token(token);
	// free_lexer(lex);
	// free_node(node);
	close(fd);
	}
	return (0);
}
