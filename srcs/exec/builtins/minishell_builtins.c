/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:16:18 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/25 13:58:21 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo_bis(t_cmd *cmd, char **tmp_arg)
{
	if (tmp_arg[1] && !ft_strcmp(tmp_arg[1], "-n"))
		ft_echo(tmp_arg[2], true, &(cmd->envp_ref), cmd);
	else
		ft_echo(tmp_arg[1], false, &(cmd->envp_ref), cmd);
	return ;
}

int	search_builtins_cmd(t_cmd *cmd)
{
	char	**tmp_arg;

	if (!cmd)
		return (0);
	tmp_arg = ft_split(cmd->arg, ' ');
	if (!tmp_arg)
		return (1);
	if (!ft_strcmp(tmp_arg[0], "export"))
		return (ft_export(&(cmd->envp_ref), tmp_arg[1]),
			free_tab((void **)tmp_arg), 1);
	else if (!ft_strcmp(tmp_arg[0], "cd"))
		return (ft_cd(cmd, &(cmd->envp_ref), tmp_arg[1]),
			free_tab((void **)tmp_arg), 1);
	else if (!ft_strcmp(tmp_arg[0], "env"))
		return (ft_env(&(cmd->envp_ref)), free_tab((void **)tmp_arg), 1);
	else if (!ft_strcmp(tmp_arg[0], "unset"))
		return (ft_unset(&(cmd->envp_ref), tmp_arg[1]),
			free_tab((void **)tmp_arg), 1);
	else if (!ft_strcmp(tmp_arg[0], "pwd"))
		return (ft_pwd(&cmd), free_tab((void **)tmp_arg), 1);
	else if (!ft_strcmp(tmp_arg[0], "exit"))
		return (ft_exit(cmd, tmp_arg[1]), free_tab((void **)tmp_arg), 1);
	else if (!ft_strcmp(tmp_arg[0], "echo"))
		return (ft_echo_bis(cmd, tmp_arg), free_tab((void **)tmp_arg), 1);
	return (free_tab((void **)tmp_arg), 0);
}
