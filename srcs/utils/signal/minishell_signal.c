/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:46:51 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/05 21:13:15 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handler(int sig)
{
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}
void    ft_signal(void)
{
    struct sigaction signal;

    signal.sa_handler = handler;
    sigemptyset(&signal.sa_mask);
    signal.sa_flags = SA_RESTART;
    sigaction(SIGINT, &signal, NULL);
}