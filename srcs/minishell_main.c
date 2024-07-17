/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/17 17:07:04 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "./minishell_parsing/includes/print_test.h"
int g_signal = 0;

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

	if (argc != 1)
	{
		printf("Error: too many arguments\n");
		return (1);
	}
	rl_catch_signals = 0;
	envp_list = NULL;
	input_cmd = NULL;
	g_signal = 0;
	init_envp(&envp_list, envp);
	if (!search_value_envp(&envp_list, "PWD"))
		search_key_and_replace_it(&envp_list, "PWD", getcwd(0, 0));
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
		if (!check_quotes(input_cmd) && !check_par(input_cmd))
			t = lexer(input_cmd);
		if (t && !check_op(t) && !check_red(t) && !check_token_par(t))
		{
			new_lexer(&t);
			// print_token(t);
			final_lexer(t, &token);
			// print_lexer(token);
		
		// t = lexer(input_cmd);
		// new_lexer(&t);
		// final_lexer(t, &token);
		// // check_op(token);
		// // check_token_par(token);
		// t_lexer *token2;
			t_glob *glob;
			t_id	*id_node;
			glob = malloc(sizeof(t_glob) * 1);

			glob->root = token;
			glob->id_node = NULL;
		// pipe_fd[0] = 0;
		// pipe_fd[1] = 0;

			execute_ast(token, pipe_fd, &envp_list, glob);
			ft_free_id_list(&glob->id_node);
		}	
		// print_lexer(token);
		// free_everything(&token, prompt);
		// free(input_cmd);
	}
	return (0);
	
}
