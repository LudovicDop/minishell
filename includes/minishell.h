/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:11:00 by ldoppler          #+#    #+#             */
/*   Updated: 2024/05/08 18:13:07 by ldoppler         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef struct s_tab
{
    char      *prompt;
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

typedef struct s_envp
{
    char    *key;
    char    *value;
    struct s_envp *next;
} t_envp;

/*utils*/
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin2(char *s1, char *s2);
/*Minishell main function exec*/
void    execution_main(t_cmd **cmd);
/*Quêtes secondaires*/
void    special_carac(t_cmd *cmd);
int     search_builtins_cmd(t_cmd *cmd);
/*Minishell parsing*/
void    start_parsing(char *tmp, t_cmd **cmd);
/*Minishell search good path in envp*/
char    *test_good_path_for_exec(char *exec_name, char *path);
char    *search_path(t_cmd **cmd);
void    init_env_path(t_cmd **cmd);

void    init_envp(t_envp **envp_s, char **envp);
void    print_envp(t_envp *list);
void    add_node_to_envp(t_envp **list, t_envp *new_node);

/*Minishell freeing memory*/
void    free_tab(void   **my_tab);
void    free_everything(t_cmd **cmd);
void    free_envp(t_envp **list);

void    get_prompt(void);
void    ft_signal(void);
char	*ft_strchr_reverse(char *s1, char c);
#endif