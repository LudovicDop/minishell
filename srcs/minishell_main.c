/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/18 14:48:11 by ldoppler         ###   ########.fr       */
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

t_envp	*ft_search_envp_node(t_envp **envp, char *key)
{
	t_envp *current;

	current = *envp;
	while (current)
	{
		if (!ft_strcmp(current->key, key))
			return (current);
		current = current->next;
	}
	return (NULL);
}
void	ft_init_default_envp(t_envp **envp_list)
{
	t_envp *current;

	current = NULL;
	if (!search_value_envp(envp_list, "PWD"))
		search_key_and_replace_it(envp_list, "PWD", getcwd(0, 0));
	if (!search_value_envp(envp_list, "PATH"))
	{
		ft_export(envp_list, "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
		current = ft_search_envp_node(envp_list, "PATH");
		current->hidden = true;
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
	ft_init_default_envp(&envp_list);
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
		if (input_cmd && !check_str(input_cmd) && !check_quotes(input_cmd) && !check_par(input_cmd))
		{
			t = lexer(input_cmd);
			if (t && !check_op(t) && !check_red(t) && !check_token_par(t))
			{
				new_lexer(&t);
				final_lexer(t, &token);
			}
			t_glob *glob;
			t_id	*id_node;
			glob = malloc(sizeof(t_glob) * 1);

			glob->root = token;
			glob->id_node = NULL;

			execute_ast(token, pipe_fd, &envp_list, glob);
			ft_free_id_list(&glob->id_node);
		}	
		//  print_lexer(token);
		// free_everything(&token, prompt);
		free(input_cmd);
		input_cmd = NULL;
	}
	return (0);
	
}
