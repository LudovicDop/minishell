/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_absolute_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:19:40 by ldoppler          #+#    #+#             */
/*   Updated: 2024/06/24 13:56:27 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	testing_absolute_path(char *path, t_envp **envp)
{
	if (!path || path[0] == '~')
	{
		home_path(path, envp);
		return (1);
	}
	if (path[0] == '/')
	{
		absolute_path(path, envp);
		return (1);
	}
	return (0);
}

void	absolute_path(char *path, t_envp **envp)
{
	t_pwd	*pwd_lst;
	t_pwd	*new_node;

	pwd_lst = NULL;
	new_node = NULL;
	if (chdir(path) < 0)
	{
		ft_error_exec("No such file or directory\n", path);
		return ;
	}
	new_node = malloc(sizeof(t_pwd));
	if (!new_node)
		return ;
	new_node->node = getcwd(0, 0);
	if (!new_node->node)
		return (free(new_node));
	new_node->next = NULL;
	ft_add_pwd_node(&pwd_lst, new_node);
	init_pwd_w_envp(envp, &pwd_lst);
	free_pwd_lst(&pwd_lst);
	return ;
}
