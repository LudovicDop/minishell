/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:16:18 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/21 16:21:32 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_echo_merge(char **string)
{
	char	**tmp;
	char	*new_string;
	int		i;

	i = 0;
	new_string = NULL;
	tmp = string;
	if (!tmp)
		return (NULL);
	while (tmp[i])
	{
		new_string = ft_strjoin2(new_string, tmp[i]);
		if (tmp[i + 1])
			new_string = ft_strjoin2(new_string, " ");
		i++;
	}
	return (new_string);
}

void	ft_echo_bis(t_lexer *token, t_envp *envp_list)
{
	char	*tmp;

	tmp = NULL;
	if (token->value[1] && !ft_strcmp(token->value[1], "-n"))
	{
		tmp = ft_echo_merge(&token->value[2]);
		ft_echo(tmp, true, &(envp_list), token);
		free(tmp);
	}
	else
	{
		tmp = ft_echo_merge(&token->value[1]);
		ft_echo(tmp, false, &(envp_list), token);
		free(tmp);
	}
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
