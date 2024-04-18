/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:11:00 by ldoppler          #+#    #+#             */
/*   Updated: 2024/04/18 14:47:28 by ludovicdopp      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <time.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_tab
{
    int       *pipe_fd;
    pid_t     *process_id;
    int       nbre_cmd;
} t_tab;

typedef struct s_cmd
{
    char    *pathname;
    char    **arg;
    char    **envp;
    bool    last_cmd;
    t_tab   *tab_ref;
} t_cmd;

void    execution_main(t_cmd **cmd);
#endif