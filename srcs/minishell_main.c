/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:10:56 by ldoppler          #+#    #+#             */
/*   Updated: 2024/06/25 10:21:01 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	// t_tab	*glob;
	char	*input_cmd;
	char	*prompt;
	t_cmd	*cmd_list;
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
		cmd_list = NULL;
		prompt = get_prompt(envp_list);
		input_cmd = readline(prompt);
		if (!input_cmd)
		{
			free_envp(&envp_list);
			free(prompt);
			free(input_cmd);
			return (0);
		}
		start_parsing(input_cmd, &cmd_list, &envp_list);
		if (*input_cmd != '\0')
			add_history(input_cmd);
		execution_main(&cmd_list);
		free_everything(&cmd_list, prompt);
		free(input_cmd);
	}
	return (0);
}
