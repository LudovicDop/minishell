/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/15 16:02:57 by ldoppler         ###   ########.fr       */
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
	input_cmd = NULL;
	init_envp(&envp_list, envp);
	increment_shlvl(&envp_list);
	while (1)
	{
		init_signal(1);
		prompt = get_prompt(envp_list);
		input_cmd = readline(prompt);
		if (!input_cmd)
		{
			printf("exit\n");
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
		t_glob *glob;
		t_id	*id_node;
		glob = malloc(sizeof(t_glob) * 1);

		glob->root = token;
		glob->id_node = NULL;

		execute_ast(token, pipe_fd, envp_list, glob);
		ft_free_id_list(&glob->id_node);
		
		print_lexer(token);
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
