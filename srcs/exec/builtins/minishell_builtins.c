/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:16:18 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/20 17:24:53 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo_bis(t_lexer *token, t_envp *envp_list)
{
	if (token->value[1] && !ft_strcmp(token->value[1], "-n"))
		ft_echo(token->value[2], true, &(envp_list), token);
	else
		ft_echo(token->value[1], false, &(envp_list), token);
	return ;
}

int	search_builtins_token(t_lexer *token, t_envp **envp_list, t_glob *glob)
{
	int	i;

	i = 1;
	if (!token)
		return (0);
	if (!ft_strcmp(token->value[0], "export"))
		return (ft_export(envp_list, token->value[1]), 1);
	else if (!ft_strcmp(token->value[0], "cd"))
		return (ft_cd(token, envp_list, token->value[1]), 1);
	else if (!ft_strcmp(token->value[0], "env"))
		return (ft_env(envp_list), 1);
	else if (!ft_strcmp(token->value[0], "unset"))
	{
		while (token->value[i])
			ft_unset(envp_list, token->value[i++]);
		return (1);
	}
	else if (!ft_strcmp(token->value[0], "pwd"))
		return (ft_pwd(*envp_list), 1);
	else if (!ft_strcmp(token->value[0], "exit"))
		return (ft_exit(token, token->value[1], glob), 1);
	else if (!ft_strcmp(token->value[0], "echo"))
		return (ft_echo_bis(token, *envp_list), 1);
	return (0);
}
