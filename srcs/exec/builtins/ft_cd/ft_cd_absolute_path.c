/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_absolute_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:19:40 by ldoppler          #+#    #+#             */
/*   Updated: 2024/06/05 15:49:26 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

