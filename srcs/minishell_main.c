/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/09 21:01:26 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./minishell_parsing/includes/print_test.h"

void	free_token(t_token *token)
{
	t_token	*tmp;
	while (token)
	{
		tmp = token;
		free(token->value);
		token = token->next;
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

int	main(int argc, char **argv, char **envp)
{
	char	*input_cmd;
	char	*prompt;
	t_token	*t;
	t_lexer	*token;
	t_envp	*envp_list;
	int pipe_fd[2];

	rl_catch_signals = 0;
	envp_list = NULL;
	init_envp(&envp_list, envp);
	increment_shlvl(&envp_list);
	while (1)
	{
		init_signal(1);
		prompt = get_prompt(envp_list);
		input_cmd = readline(prompt);
		if (!input_cmd)
		{
			free_envp(&envp_list);
			free(prompt);
			free(input_cmd);
			return (0);
		}
		if (*input_cmd != '\0')
			add_history(input_cmd);
		// // check_quotes(input_cmd);
		// // check_par(input_cmd);
		t = lexer(input_cmd);
		new_lexer(&t);
		final_lexer(t, &token);
		// // check_op(token);
		// // check_token_par(token);
		// t_lexer *token2;
		t_lexer *root;

		// token = malloc(sizeof(t_lexer));
		// token2 = malloc(sizeof(t_lexer));
		// token->value = malloc(sizeof(char*) * 2);
		// token->value[0] = ft_strdup("fichier.txt");
		// token->value[1] = NULL;
		// token->type = REDIRECT_IN;
		// token->next = token2;

		// token2->value = malloc(sizeof(char*) * 2);
		// token2->value[0] = ft_strdup("cat");
		// token2->value[1] = NULL;
		// token2->type = CMD;
		// token2->next = NULL;

	
		root = token;
		// pipe_fd[0] = -1;
		// pipe_fd[1] = -1;
		// pipe_fd[0] = 0;
		// pipe_fd[1] = 0;
		int old_fd = dup(STDIN_FILENO);
		execute_ast(token, pipe_fd, envp_list, root);
		// print_lexer(token);
		// print_token(t);
		// free_everything(&token, prompt);
		// free(input_cmd);
	}
	return (0);
	
}


// int	main(int ac, char **av)
// {
// 	int		fd;
// 	char	*str;
// 	t_token	*token;
// 	t_node	*node;

// 	if (ac != 2)
// 	{
// 		ft_printf("Error arguments\n");
// 		exit(1);
// 	}
// 	fd = open(av[1], O_RDONLY);
// 	if (fd == -1)
// 	{
// 		ft_printf("Error open file\n");
// 		exit(1);
// 	}
// 	str = get_next_line(fd);
// 	printf("%s", str);
// 	check_quotes(str);
// 	check_par(str);
// 	token = lexer(str);
// 	check_op(token);
// 	check_token_par(token);
// 	node = parse(token);
// 	free(str);
// 	while ((str = get_next_line(fd)))
// 		free(str);
// 	free_token(token);
// 	free_node(node);
	
// 	return (0);
// }
