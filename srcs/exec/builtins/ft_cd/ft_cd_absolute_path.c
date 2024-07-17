/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_absolute_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:19:40 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/17 17:33:45 by ldoppler         ###   ########.fr       */
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
	if (path[0] == '-')
	{
		go_old_pwd(envp);
		return (1);
	}
	return (0);
}

void	absolute_path(char *path, t_envp **envp)
{
	char	*old_pwd;
	t_pwd	*pwd_lst;
	t_pwd	*new_node;

	old_pwd = getcwd(0, 0);
	pwd_lst = NULL;
	new_node = NULL;
	if (ft_chdir(path) < 0)
		return (free(old_pwd));
	search_key_and_replace_it(envp, "OLDPWD", old_pwd);
	free(old_pwd);
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
