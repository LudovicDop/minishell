/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:09:55 by ldoppler          #+#    #+#             */
/*   Updated: 2024/06/12 22:38:37 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*search_envp_value(t_envp **envp, char *key)
{
	t_envp	*current;

	current = *envp;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			return (current);
		}
		current = current->next;
	}
    return (NULL);
}

char     *skip_dollar(char *string)
{
    int i;
    int j;
    int lenght;

    j = 0;
    i = 0;
    lenght = ft_strlen(string);
    while (i < lenght)
    {
        if (string[i] != '$')
            string[j] = string[i];
        else if (string[i] == '$')
            j--;
        j++;
        i++;
    }
    string[j] = '\0';
    return (string);
}

char    *ft_check_dollar(char *string, t_envp **envp, t_cmd *cmd)
{
    t_envp *node;

    if (!ft_strcmp(string, "$"))
        return ("$");
    if (!ft_strcmp(string, "$?"))
        return (ft_itoa(cmd->tab_ref->return_val));
    if (string[0] == '$')
    {
        node = search_envp_value(envp, skip_dollar(string));
        if (node)
            return (node->value);
        else
            return ("");
    }
    return (string);
}

void    ft_echo(char *string, bool without_ret, t_envp **envp, t_cmd *cmd)
{
    if (!string)
    {
        printf("\n");
        return ;
    }
    if (without_ret)
    {
        printf("%s", ft_check_dollar(string, envp, cmd));
    }
    else if (!without_ret)
    {
        printf("%s\n", ft_check_dollar(string, envp, cmd));
    }
}