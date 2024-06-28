/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 01:36:43 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/28 12:29:14 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(t_envp **envp, char *key)
{
	t_envp	*envp_tmp;

	envp_tmp = *envp;
	while (envp_tmp)
	{
		if (!ft_strcmp(envp_tmp->key, key))
		{
			return (envp_tmp->value);
		}
		envp_tmp = envp_tmp->next;
	}
	return (NULL);
}

char	*pwd_until_slash(char *pwd)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!pwd)
		return (NULL);
	while (pwd[j] && pwd[j] != '/')
		j++;
	ret = malloc(sizeof(char) * j + 2);
	while (pwd[i])
	{
		ret[i] = pwd[i];
		if (pwd[i] == '/')
		{
			i++;
			ret[i] = '\0';
			return (ret);
		}
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

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

int		compare_path(t_envp **envp, char *path)
{
	// char *tmp;

	// tmp = getcwd(0, 0);
	printf("path : %s\n", path);
	if (is_symbolic_link(path) == 1)
	{
		printf("symbolic\n");
	}
	else
	{
		printf("not symbolic\n");
	}
	return (0);
}

void remove_last_node(t_pwd **pwd_lst)
{
    t_pwd *current;
    t_pwd *previous;

    current = *pwd_lst;
    if (!current)
        return ;

    if (!current->next) // Case when there's only one node
    {
        printf("Last node: %s\n", current->node);
        free(current->node);
        free(current);
        *pwd_lst = NULL;
        return ;
    }

    // Traverse to the second-to-last node
    while (current->next)
    {
        previous = current;
        current = current->next;
    }

    printf("Last node: %s\n", current->node);
    free(current->node);
    free(current);
	remove_backslash_end(&(previous->node)); 
    previous->next = NULL;
}

int	update_old_pwd(char *current_pwd, t_envp **envp)
{
	char	*tmp;
	t_pwd *update_old_path;

	update_old_path = NULL;
	if (is_symbolic_link(current_pwd) == 1)
	{
		parse_pwd(&update_old_path, search_value_envp(envp, "PWD"));
		remove_last_node(&update_old_path);
		init_pwd_w_envp(envp, &update_old_path);
		return (1);
	}
	else
	{
		tmp = getcwd(0, 0);
		search_key_and_replace_it(envp, "PWD", tmp);
		free(tmp);
	}
	return (0);
}

void	ft_cd(t_token *token, t_envp **envp, char *path)
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
	{
		if (update_old_pwd(old_pwd, envp))
			return ;
	}
	printf("==> %s\n", path);
	if (chdir(path) < 0)
	{
		// cmd->tab_ref->return_val = 42;
		return (ft_error_exec("No such file or directory\n", path), free(old_pwd));
	}
	new_node = malloc(sizeof(t_pwd));
	if (!new_node)
		return ;
	tmp = ft_strtrim(path, "./");
	if (!tmp)
		return (free(new_node));
	search_key_and_replace_it(envp, "OLDPWD", old_pwd);
	if (tmp[0] != '\0')
	{
		new_node->node = ft_strjoin("/", tmp);
	}
	else
		new_node->node = getcwd(0, 0);
	new_node->next = NULL;
	method_of_list(path, new_node, envp);
	// free(old_pwd);
	free(tmp);
}
