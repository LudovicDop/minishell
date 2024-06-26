/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:15:46 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/04 17:48:28 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_users(char *string)
{
	int		i;
	char	*s1;
	char	*new_path;
	int		lenght;

	i = 0;
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
	tmp_user = ft_strjoin2(tmp_user, "\033[m:");
	return (tmp_user);
}

char	*init_prompt_path(char *tmp_path, t_envp **envp_list)
{
	t_envp	*current;

	current = *envp_list;
	tmp_path = ft_strjoin("\033[35;1m", remove_users(current->value));
	tmp_path = ft_strjoin2(tmp_path, "\033[m ");
	if (ft_strlen(tmp_path) == 11)
	{
		free(tmp_path);
		tmp_path = ft_strdup("\033[35;1m/\033[m ");
	}
	return (tmp_path);
}

char	*get_prompt(t_envp *envp_list)
{
	char	*tmp_user;
	char	*tmp_path;
	char	*prompt;
	int		i;
	t_envp	*current;

	tmp_user = NULL;
	tmp_path = NULL;
	prompt = NULL;
	current = envp_list;
	i = 0;
	while (current)
	{
		if (!ft_strcmp(current->key, "USER"))
			tmp_user = init_prompt_user(tmp_user, &current);
		if (*(current->value) != '\0' && !ft_strcmp(current->key, "PWD"))
			tmp_path = init_prompt_path(tmp_path, &current);
		current = current->next;
	}
	prompt = ft_strjoin(tmp_user, tmp_path);
	if (!prompt)
		return (NULL);
	return (free(tmp_user), free(tmp_path), prompt);
}
