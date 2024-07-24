/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/24 18:07:39 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell_parsing/includes/print_test.h"
#include "minishell.h"

int		g_signal = 0;

t_envp	*ft_search_envp_node(t_envp **envp, char *key)
{
	t_envp	*current;

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
	t_envp	*current;

	current = NULL;
	if (!search_value_envp(envp_list, "PWD"))
		search_key_and_replace_it(envp_list, "PWD", getcwd(0, 0));
	if (!search_value_envp(envp_list, "PATH"))
	{
		ft_export(envp_list, PATH_DEF);
		current = ft_search_envp_node(envp_list, "PATH");
		current->hidden_bis = true;
	}
}

void	ft_parsing_check(t_glob *glob, t_envp *envp_list, t_lexer **token)
{
	t_token	*t;

	if (glob->input_cmd && !check_str(glob->input_cmd)
		&& !check_quotes(glob->input_cmd) && !check_par(glob->input_cmd))
	{
		t = lexer(glob->input_cmd);
		if (t && !check_op(t) && !check_red(t) && !check_token_par(t))
		{
			new_lexer(&t, &envp_list);
			final_lexer(t, token);
			// print_token(t);
			// print_lexer(*token);
		}
		free_token(t);
	}
}

void	ft_init_minishell(t_envp **envp_list, char **envp, t_glob **glob,
		char **argv)
{
	rl_catch_signals = 0;
	*envp_list = NULL;
	g_signal = 0;
	(void)argv;
	init_envp(envp_list, envp);
	ft_init_default_envp(envp_list);
	increment_shlvl(envp_list);
	*glob = malloc(sizeof(t_glob) * 1);
	if (!*glob)
		return (free_envp(envp_list), exit(EXIT_FAILURE));
}

int	main(int argc, char **argv, char **envp)
{
	t_envp		*envp_list;
	t_glob		*glob;
	t_lexer		*token;
	static int	pipe_fd[2];

	if (argc != 1)
		return (printf("Error: too many arguments\n"), 1);
	ft_init_minishell(&envp_list, envp, &glob, argv);
	while (1)
	{
		token = NULL;
		init_signal(1);
		glob->prompt = get_prompt(envp_list);
		glob->input_cmd = readline(glob->prompt);
		if (!glob->input_cmd)
			return (ft_exit_minishell(&glob, &envp_list));
		if (*(glob->input_cmd) != '\0')
			add_history(glob->input_cmd);
		ft_parsing_check(glob, envp_list, &token);
 		ft_init_glob(&glob, &token, &envp_list);
		execute_ast(token, pipe_fd, &envp_list, glob);
		ft_free_id_list(&glob->id_node);
		ft_minishell_free(&token, &glob);
	}
	return (0);
}
