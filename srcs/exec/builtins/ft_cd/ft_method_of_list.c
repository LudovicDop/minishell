/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_method_of_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 13:29:38 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/08 13:36:12 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_symbolic_link(const char *path) {
    struct stat path_stat;
    
    // Use lstat to get the information about the path
    if (lstat(path, &path_stat) != 0) {
        return -1; // Error occurred
    }

    // Check if the path is a symbolic link
    if (S_ISLNK(path_stat.st_mode)) {
        return 1; // The path is a symbolic link
    } else {
        return 0; // The path is not a symbolic link
    }
}

void    method_of_list(char *path, t_pwd *pwd_lst, t_pwd *new_node, t_envp **envp)
{
    if (is_symbolic_link(path) == 1)
    {
        ft_add_pwd_node(&pwd_lst, new_node);
        init_pwd_w_envp(envp, &pwd_lst);
    }
    else if (is_symbolic_link(path) <= 0)
        search_key_and_replace_it(envp, "PWD", getcwd(0, 0));
}
