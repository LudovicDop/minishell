/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/06/27 16:55:51 by ldoppler         ###   ########.fr       */
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
	// t_tab	*glob;
	char	*input_cmd;
	char	*prompt;
	t_token	*token;
	// t_cmd	*cmd_list;
	t_envp	*envp_list;

	// glob = ft_calloc(sizeof(t_tab), 1);
	// if (!glob)
	// 	return (1);
	envp_list = NULL;
	init_envp(&envp_list, envp);
	init_signal();
	increment_shlvl(&envp_list);
	while (1)
	{
		// cmd_list = NULL;
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
		// check_quotes(input_cmd);
		// check_par(input_cmd);
		token = lexer(input_cmd);
		int pipe_fd[2];
		pipe(pipe_fd);
		// pipe_fd[0] = -1;
		// pipe_fd[1] = -1;
		t_token *root;

		root = token;
		execute_ast(token, pipe_fd, envp_list, root);
		// check_op(token);
		// check_token_par(token);
		print_token(token);
		// start_parsing(input_cmd, &cmd_list, &envp_list);
		// execution_main(&cmd_list);
		// free_everything(&cmd_list, prompt);
		free(input_cmd);
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
