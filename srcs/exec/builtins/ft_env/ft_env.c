/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:59:05 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/06/01 22:04:36 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_env(t_envp **envp_list)
{
   t_envp *current;

   current =  *envp_list;
   while (current)
   {
        printf("%s=", current->key);
        printf("%s\n", current->value);
        current = current->next;
   }
   return ;
}