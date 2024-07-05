/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:16:18 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/05 15:14:32 by ldoppler         ###   ########.fr       */
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

int	search_builtins_token(t_lexer *token, t_envp *envp_list)
{
	if (!token)
		return (0);
	// token->value = ft_split(token->value, ' ');
	// if (!token->value)
	// 	return (1);
	if (!ft_strcmp(token->value[0], "export"))
		return (ft_export(&(envp_list), token->value[1]), 1);
	else if (!ft_strcmp(token->value[0], "cd"))
		return (ft_cd(token, &(envp_list), token->value[1]), 1);
	else if (!ft_strcmp(token->value[0], "env"))
		return (ft_env(&(envp_list)), free_tab((void **)token->value), 1);
	else if (!ft_strcmp(token->value[0], "unset"))
		return (ft_unset(&(envp_list), token->value[1]), 1);
	else if (!ft_strcmp(token->value[0], "pwd"))
		return (ft_pwd(envp_list), 1);
	else if (!ft_strcmp(token->value[0], "exit"))
		return (ft_exit(token, token->value[1]), 1);
	else if (!ft_strcmp(token->value[0], "echo"))
		return (ft_echo_bis(token, envp_list), 1);
	return (0);
}
