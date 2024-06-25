/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_method_of_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:29:38 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/25 09:01:45 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_symbolic_link(const char *path)
{
	struct stat	path_stat;

	if (lstat(path, &path_stat) != 0)
		return (-1);
	if (S_ISLNK(path_stat.st_mode))
		return (1);
	else
		return (0);
}

void	method_of_list(char *path, t_pwd *new_node, t_envp **envp)
{
	char	*tmp;
	t_pwd	*pwd_lst;

	pwd_lst = NULL;
	if (is_symbolic_link(path) == 1)
	{
		parse_pwd(&pwd_lst, search_value_envp(envp, "PWD"));
		ft_add_pwd_node(&pwd_lst, new_node);
		init_pwd_w_envp(envp, &pwd_lst);
		free_pwd_lst(&pwd_lst);
	}
	else if (is_symbolic_link(path) <= 0)
	{
		tmp = getcwd(0, 0);
		search_key_and_replace_it(envp, "PWD", tmp);
		free(new_node->node);
		free(new_node);
		free(tmp);
	}
}
