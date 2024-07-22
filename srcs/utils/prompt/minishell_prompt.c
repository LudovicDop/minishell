/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:15:46 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/07/22 16:21:47 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_users(char *string)
{
	char	*s1;
	char	*new_path;

	s1 = string;
	if (!*s1)
		return (NULL);
	s1++;
	while (*s1 != '\0' && *s1 != '/')
		s1++;
	new_path = s1;
	return (new_path);
}

char	*init_prompt_user(char *tmp_user, t_envp **envp_list)
{
	t_envp	*current;

	current = *envp_list;
	tmp_user = ft_strjoin("\033[32;1m@", current->value);
	if (!tmp_user)
		return (NULL);
	tmp_user = ft_strjoin2(tmp_user, "\033[m:");
	if (!tmp_user)
		return (free(tmp_user), NULL);
	return (tmp_user);
}

char	*init_prompt_path(char *tmp_path, t_envp **envp_list)
{
	t_envp	*current;

	current = *envp_list;
	tmp_path = ft_strjoin("\033[35;1m", remove_users(current->value));
	if (!tmp_path)
		return (NULL);
	tmp_path = ft_strjoin2(tmp_path, "\033[m ");
	if (!tmp_path)
		return (NULL);
	if (ft_strlen(tmp_path) == 11)
	{
		free(tmp_path);
		tmp_path = ft_strdup("\033[35;1m/\033[m ");
		if (!tmp_path)
			return (NULL);
	}
	return (tmp_path);
}

char	*init_prompt_path2(void)
{
	char	*tmp;
	char	*cwd;
	char	*without_user;

	cwd = getcwd(0, 0);
	if (!cwd)
		return (NULL);
	without_user = remove_users(cwd);
	tmp = ft_strjoin("\033[35;1m", without_user);
	if (!tmp)
		return (free(cwd), NULL);
	tmp = ft_strjoin2(tmp, "\033[m ");
	if (!tmp)
		return (free(cwd), NULL);
	if (ft_strlen(tmp) == 11)
	{
		tmp = ft_strdup("\033[35;1m/\033[m ");
		if (!tmp)
			return (free(cwd), NULL);
	}
	return (free(cwd), tmp);
}

char	*get_prompt(t_envp *envp_list)
{
	char	*tmp_user;
	char	*tmp_path;
	char	*prompt;
	t_envp	*current;

	tmp_user = NULL;
	tmp_path = NULL;
	prompt = NULL;
	current = envp_list;
	while (current)
	{
		ft_search_prompt_val(&current, &tmp_path, &tmp_user);
		current = current->next;
	}
	if (tmp_user && tmp_path)
	{
		prompt = ft_strjoin(tmp_user, tmp_path);
		if (!prompt)
			return (NULL);
	}
	else
		return (ft_empty_envp_prompt(tmp_path, prompt, tmp_user));
	return (free(tmp_user), free(tmp_path), prompt);
}
