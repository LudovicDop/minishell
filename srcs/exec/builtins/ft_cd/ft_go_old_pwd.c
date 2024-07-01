/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_old_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:12:42 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/01 17:01:27 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_old_pwd(t_envp **envp)
{
	char	*old_pwd;

	old_pwd = search_value_envp(envp, "OLDPWD");
	if (chdir(old_pwd) < 0)
	{
		ft_putstr_fd("nemshell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	search_key_and_replace_it(envp, "PWD", old_pwd);
	return (0);
}
