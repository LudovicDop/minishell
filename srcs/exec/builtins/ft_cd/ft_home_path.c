/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_home_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:48:38 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/01 16:59:16 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	c_is_present(char *string, char c)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*start_replacing(char *string, char *new_string, char c_to_replace,
		char *insert)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	j = 0;
	while (string[i])
	{
		if (string[i] == c_to_replace)
		{
			i++;
			while (insert[j])
				new_string[k++] = insert[j++];
		}
		new_string[k++] = string[i];
		if (string[i])
			i++;
	}
	new_string[k] = '\0';
	return (new_string);
}

char	*search_and_replace(char *string, char c_to_replace, char *insert)
{
	char	*new_string;

	if (!string || !c_to_replace || !insert)
		return (string);
	if (c_is_present(string, c_to_replace))
	{
		new_string = malloc(sizeof(char) * ft_strlen(string) + ft_strlen(insert)
				+ 1);
		if (!new_string)
			return (NULL);
		return (start_replacing(string, new_string, c_to_replace, insert));
	}
	new_string = ft_strdup(string);
	if (!new_string)
		return (NULL);
	return (new_string);
}

void	remove_backslash_end(char **path)
{
	int	i;

	i = 0;
	if (!*path)
		return ;
	i = ft_strlen(*path);
	if ((*path)[i - 1] == '/')
	{
		(*path)[i - 1] = '\0';
	}
}

void	home_path(char *path, t_envp **envp)
{
	char	*new_path;

	new_path = NULL;
	if (path)
		new_path = search_and_replace(path, '~', search_value_envp(envp,
					"HOME"));
	else
	{
		new_path = search_value_envp(envp, "HOME");
	}
	if (chdir(new_path) < 0)
	{
		if (!new_path)
			ft_putstr_fd("nemshell : HOME is probably unset!\n", 2);
		else
			ft_error_exec("No such file or directory\n", new_path);
		return ;
	}
	remove_backslash_end(&new_path);
	search_key_and_replace_it(envp, "PWD", new_path);
	return ;
}
