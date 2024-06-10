/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_absolute_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:19:40 by ldoppler          #+#    #+#             */
/*   Updated: 2024/06/08 13:25:40 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     testing_absolute_path(char *path, t_envp **envp, t_pwd *pwd_lst)
{
    if (!path || path[0] == '~')
    {
        home_path(path, envp);
        return (1);
    }
    if (path[0] == '/')
    {
        absolute_path(path, &pwd_lst, envp);
        return (1);
    }
    return (0);
}
void    absolute_path(char *path, t_pwd **pwd_lst, t_envp **envp)
{
    t_pwd *new_node;

    new_node = NULL;
    if (chdir(path) < 0)
    {
        perror("chdir");
        return ;
    } 
    new_node = malloc(sizeof(t_pwd));
    new_node->node = getcwd(0, 0);
    new_node->next = NULL;
    ft_add_pwd_node(pwd_lst, new_node);
    init_pwd_w_envp(envp, pwd_lst);
    return ;
}

