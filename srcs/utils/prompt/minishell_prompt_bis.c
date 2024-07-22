/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prompt_bis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:57:40 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/22 16:10:52 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_empty_envp_prompt(char *tmp_path, char *prompt, char *tmp_user)
{
	if (tmp_path)
		free(tmp_path);
	prompt = ft_strdup("\033[32;1m@?\033[m:");
	if (!prompt)
		return (free(tmp_user), free(tmp_path), NULL);
	tmp_path = init_prompt_path2();
	prompt = ft_strjoin2(prompt, tmp_path);
	if (!prompt)
		return (free(tmp_user), free(tmp_path), NULL);
	return (free(tmp_user), free(tmp_path), prompt);
}

void	ft_search_prompt_val(t_envp **current, char **tmp_path, char **tmp_user)
{
	if (*current && !ft_strcmp((*current)->key, "USER"))
		*tmp_user = init_prompt_user(*tmp_user, current);
	else if ((*current)->value[0] != '\0' && !ft_strcmp((*current)->key, "PWD"))
		*tmp_path = init_prompt_path(*tmp_path, current);
}
