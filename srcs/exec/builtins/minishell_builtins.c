/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:16:18 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/30 20:09:43 by ldoppler         ###   ########.fr       */
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
		if (!new_string)
			return (NULL);
		if (tmp[i + 1] && ft_strncmp(tmp[i], "", 1))
		{
			new_string = ft_strjoin2(new_string, " ");
			if (!new_string)
				return (NULL);
		}
		i++;
	}
	return (new_string);
}

int	ft_check_after_n(char *string)
{
	int	i;

	i = 0;
	if (!string)
		return (0);
	while (string[i])
	{
		if (string[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo_bis(t_lexer *token)
{
	char	*tmp;
	int		i;

	i = 1;
	tmp = NULL;
	if (token->value[1] && !ft_strncmp(token->value[1], "-n", 2))
	{
		while (token->value[i] && !ft_strncmp(token->value[i], "-n", 2))
		{
			if (!ft_check_after_n(token->value[i] + 1))
				i++;
			else
				break ;
		}
		if (token->value[i])
			ft_echo_bis2(tmp, token, i);
		else
			ft_echo("", true);
		return ;
	}
	else
		ft_echo_bis2(tmp, token, 1);
	return ;
}

void	ft_export_bis(t_lexer *token, t_envp **envp_list, int i)
{
	g_signal = 0;
	if (!token->value[1])
		ft_export(envp_list, token->value[1]);
	while (token->value[i])
		ft_export(envp_list, token->value[i++]);
}

int	search_builtins_token(t_lexer *token, t_envp **envp_list, t_glob *glob,
		int *pipe_fd)
{
	int	i;

	i = 1;
	if (!token)
		return (0);
	if (!ft_strcmp(token->value[0], "export"))
		return (ft_export_bis(token, envp_list, i), 1);
	else if (!ft_strcmp(token->value[0], "cd"))
		return (ft_cd(envp_list, token->value[1]), 1);
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
		return (ft_exit_bis(token, envp_list, glob, pipe_fd),
			ft_exit(token->value[1], glob, pipe_fd), 1);
	else if (!ft_strcmp(token->value[0], "echo"))
		return (ft_echo_bis(token), 1);
	return (0);
}
