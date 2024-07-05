/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:36:43 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/05 14:36:58 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pwd_bis(t_pwd **pwd_lst, char *pwd_value, int i)
{
	t_pwd	*new_node;

	new_node = NULL;
	new_node = malloc(sizeof(t_pwd));
	if (!new_node)
		return (1);
	new_node->node = pwd_until_slash(pwd_value + i);
	new_node->next = NULL;
	new_node->root = false;
	ft_add_pwd_node(pwd_lst, new_node);
	return (0);
}

void	parse_pwd(t_pwd **pwd_lst, char *pwd_value)
{
	int		i;
	char	*tmp;
	t_pwd	*new_node;

	i = 0;
	new_node = malloc(sizeof(t_pwd));
	if (!new_node)
		return ;
	new_node->node = ft_strdup("/");
	if (!new_node->node)
		return ;
	new_node->next = NULL;
	ft_add_pwd_node(pwd_lst, new_node);
	while (pwd_value[i])
	{
		if (pwd_value[i] && pwd_value[i] == '/')
		{
			i++;
			parse_pwd_bis(pwd_lst, pwd_value, i);
		}
		if (pwd_value[i])
			i++;
	}
}

void	remove_last_node(t_pwd **pwd_lst)
{
	t_pwd	*current;
	t_pwd	*previous;

	current = *pwd_lst;
	if (!current)
		return ;
	if (!current->next)
	{
		free(current->node);
		free(current);
		*pwd_lst = NULL;
		return ;
	}
	while (current->next)
	{
		previous = current;
		current = current->next;
	}
	free(current->node);
	free(current);
	remove_backslash_end(&(previous->node));
	previous->next = NULL;
}

int	update_old_pwd(char *current_pwd, t_envp **envp, char *path)
{
	char	*tmp;
	t_pwd	*update_old_path;

	update_old_path = NULL;
	if (is_symbolic_link(current_pwd) == 1)
	{
		search_key_and_replace_it(envp, "OLDPWD", current_pwd);
		parse_pwd(&update_old_path, search_value_envp(envp, "PWD"));
		remove_last_node(&update_old_path);
		init_pwd_w_envp(envp, &update_old_path);
		free_pwd_lst(&update_old_path);
		return (1);
	}
	else
	{
		if (!ft_chdir(path))
			return (1);
		tmp = getcwd(0, 0);
		search_key_and_replace_it(envp, "OLDPWD", current_pwd);
		search_key_and_replace_it(envp, "PWD", tmp);
		free(tmp);
		return (1);
	}
	return (0);
}

void	ft_cd(t_lexer *token, t_envp **envp, char *path)
{
	char	*current_pwd;
	char	*old_pwd;
	char	*tmp;
	t_pwd	*new_node;

	new_node = NULL;
	old_pwd = search_value_envp(envp, "PWD");
	if (testing_absolute_path(path, envp))
		return ;
	if (!ft_strcmp(path, ".."))
		if (update_old_pwd(old_pwd, envp, path))
			return ;
	if (!ft_chdir(path))
		return ;
	new_node = malloc(sizeof(t_pwd));
	if (!new_node)
		return ;
	tmp = ft_strtrim(path, "./");
	if (!tmp)
		return (free(new_node));
	search_key_and_replace_it(envp, "OLDPWD", old_pwd);
	ft_cd_add_slash(tmp, new_node);
	return (method_of_list(path, new_node, envp), free(tmp));
}
