/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ludovicdoppler <ludovicdoppler@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:11:00 by ldoppler          #+#    #+#             */
/*   Updated: 2024/04/29 17:52:51 by ludovicdopp      ###   ########.fr       */
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
# include "../libft/libft.h"
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <time.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_tab
{
    int       pipe_fd[2];
    pid_t     *process_id;
    int       nbre_cmd;
    char      **envp;
    char      *tmp;
} t_tab;

typedef struct s_cmd
{
    char    *pathname;
    char    **arg;
    char    **envp;
    char    **arg_redirection;
    bool    any_redirection;
    bool    last_cmd;
    t_tab   *tab_ref;
} t_cmd;
/*utils*/
int	ft_strcmp(const char *s1, const char *s2);
/*Minishell main function exec*/
void    execution_main(t_cmd **cmd);
void    special_carac(t_cmd *cmd);
int search_builtins_cmd(t_cmd *cmd);
void    start_parsing(char *tmp, t_cmd **cmd);
void    free_tab(void   **my_tab);
void    free_everything(t_cmd **cmd);
#endif