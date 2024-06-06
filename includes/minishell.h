/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:11:00 by ldoppler          #+#    #+#             */
/*   Updated: 2024/06/06 16:11:51 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <curses.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <time.h>
# include <unistd.h>

typedef struct s_tab
{
	char			*prompt;
	pid_t			*process_id;
	int				pipe_fd[2];
	int				nbre_cmd;
	struct s_envp	*envp;
}					t_tab;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}					t_envp;

typedef struct s_cmd
{
	char			*pathname;
	char			*arg;
	char			*arg_redirection;
	bool			any_redirection;
	bool			last_cmd;
	t_tab			*tab_ref;
	t_envp			*envp_ref;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_export
{
	char			*key;
	char			*value;
}					t_export;

typedef struct s_pwd
{
	bool			root;
	char			*node;
	struct s_pwd	*next;
}					t_pwd;

/*utils*/
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strjoin2(char *s1, char *s2);
char				*ft_strchr2(const char *s, int c);

/*Minishell main function exec*/
void				execution_main(t_cmd **cmd);

/*Quêtes secondaires*/
void				special_carac(t_cmd *cmd);
int					search_builtins_cmd(t_cmd *cmd);

/*Minishell parsing*/
void				start_parsing(char *input_cmd, t_cmd **cmd, t_envp **envp);

/*Minishell search good path in envp*/
void				ft_env(t_envp **envp_list);
char				*test_good_path_for_exec(char *exec_name, char *path);
char				*search_path(t_cmd **cmd);
char				**convert_envp(t_envp *envp_list);
t_envp				**search_envp_key(t_envp **envp, char *key);

void				init_envp(t_envp **envp_list, char **envp);
void				print_envp(t_envp *list);
void				add_cmd_node(t_cmd *new_node, t_cmd **cmd_lst,
						t_tab **global, t_envp **envp);

/*Minishell freeing memory*/
void				free_tab(void **my_tab);
void				free_everything(t_cmd **cmd, char *prompt);
void				free_envp(t_envp **list);
void				free_cmd_list(t_cmd **cmd_list);

char				*get_prompt(t_envp *envp_list);
void				ft_signal(void);
char				*ft_strchr_reverse(char *s1, char c);

/*builtins*/
void				ft_export(t_envp **envp_list, char *key_value);
void				ft_cd(t_envp **envp, char *path);
int					search_builtins_child(t_cmd *cmd);

/*SIGNAL*/
void				handler(int signal);
void				init_signal(void);

void				search_key_and_replace_it(t_envp **envp, char *key,
						char *value);
char				*get_key(t_envp **envp, char *key);
/*CD*/
void    ft_add_pwd_node(t_pwd **pwd_lst, t_pwd *node);
void    init_pwd_w_envp(t_envp **envp, t_pwd **pwd_lst);
int     nbre_node(t_pwd **pwd_list);
void    remove_last_node_pwd(t_pwd **pwd_list);
void    remove_slash(t_pwd **pwd_node);
void    absolute_path(char *path, t_pwd **pwd_lst, t_envp **envp);
char    *remove_backslash_at_end(char *pwd);
void    free_pwd_lst(t_pwd **pwd);
void    home_path(char *path, t_envp **envp);
/*PWD*/
void    ft_pwd(t_cmd **cmd);
#endif