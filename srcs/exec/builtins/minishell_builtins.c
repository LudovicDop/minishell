/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:16:18 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/03 12:28:13 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo_bis(t_token *token, char **tmp_arg, t_envp *envp_list)
{
	if (tmp_arg[1] && !ft_strcmp(tmp_arg[1], "-n"))
		ft_echo(tmp_arg[2], true, &(envp_list), token);
	else
		ft_echo(tmp_arg[1], false, &(envp_list), token);
	return (free_tab((void **)tmp_arg));
}

int	search_builtins_token(t_token *token, t_envp *envp_list)
{
	char	**tmp_arg;

	if (!token)
		return (0);
	tmp_arg = ft_split(token->value, ' ');
	if (!tmp_arg)
		return (1);
	if (!ft_strcmp(tmp_arg[0], "export"))
		return (ft_export(&(envp_list), tmp_arg[1]),
			free_tab((void **)tmp_arg), 1);
	else if (!ft_strcmp(tmp_arg[0], "cd"))
		return (ft_cd(token, &(envp_list), tmp_arg[1]),
			free_tab((void **)tmp_arg), 1);
	else if (!ft_strcmp(tmp_arg[0], "env"))
		return (ft_env(&(envp_list)), free_tab((void **)tmp_arg), 1);
	else if (!ft_strcmp(tmp_arg[0], "unset"))
		return (ft_unset(&(envp_list), tmp_arg[1]),
			free_tab((void **)tmp_arg), 1);
	else if (!ft_strcmp(tmp_arg[0], "pwd"))
		return (ft_pwd(envp_list), free_tab((void **)tmp_arg), 1);
	else if (!ft_strcmp(tmp_arg[0], "exit"))
		return (ft_exit(token, tmp_arg[1]), free_tab((void **)tmp_arg), 1);
	else if (!ft_strcmp(tmp_arg[0], "echo"))
		return (ft_echo_bis(token, tmp_arg, envp_list), 1);
	return (free_tab((void **)tmp_arg), 0);
}
