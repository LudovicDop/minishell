/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:46:51 by ludovicdopp       #+#    #+#             */
/*   Updated: 2024/05/30 13:08:08 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    handler(int sig)
// {
//     //rl_replace_line("", 0);
//     rl_on_new_line();
//     rl_redisplay();
// }
// void    ft_signal(void)
// {
//     struct sigaction signal;

//     signal.sa_handler = handler;
//     sigemptyset(&signal.sa_mask);
//     signal.sa_flags = SA_RESTART;
//     sigaction(SIGINT, &signal, NULL);
// }