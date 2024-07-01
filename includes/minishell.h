/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:11:00 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/01 17:04:36 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../srcs/minishell_parsing/includes/check.h"
// # include "../srcs/minishell_parsing/includes/lexer.h"
// # include "../srcs/minishell_parsing/includes/parser.h"
// # include "../srcs/minishell_parsing/includes/print_test.h"
# include <curses.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <time.h>
# include <unistd.h>
# define WRITE 1
# define READ 0
typedef struct s_tab
{
	char			*prompt;
	pid_t			*process_id;
	int				pipe_fd[2];
	int				nbre_cmd;
	int				return_val;
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

// typedef enum
// {
// 	WORD,
// 	AND,
// 	OR,
// 	PIPE,
// 	LPARENT,
// 	RPARENT,
// 	SUBSHELL,
// 	COMMAND
// }					t_token_type;

/*New part of my code*/
// typedef struct s_node
// {
// 	t_token_type	type;
// 	char			*value;
// 	struct s_node	*left;
// 	struct s_node	*right;
// }					t_node;

typedef struct s_export
{
	char			*key;
	char			*value;
}					t_export;
/*end of the new part of my code*/

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
void				ft_error_exec(char *error_msg, char *cmd_name);
int 				execute_command(t_token *token, int *pipe_fd, t_envp *envp_list, t_token *root);
int 				execute_ast(t_token *node, int pipe[2], t_envp *envp_list, t_token *root);

/*Quêtes secondaires*/
void				special_carac(t_cmd *cmd);
int					search_builtins_cmd(t_cmd *cmd);

/*Minishell parsing*/
int					start_parsing(char *input_cmd, t_cmd **cmd, t_envp **envp);
int					check_simple_quotes(char *input_cmd, t_cmd *cmd);
int					check_double_quotes(char *input_cmd, t_cmd *cmd);
int					check_pipes(char *input_cmd, t_cmd *cmd);
int					empty_after_symbol(char *input_cmd);
int					check_redirection_symbol(char *input_cmd, t_cmd *cmd);
int					ft_error_msg(t_cmd *cmd, char *error_msg,
						char near_this_char, int error_val);

/*Minishell search good path in envp*/
void				ft_env(t_envp **envp_list);
char				*test_good_path_for_exec(char *exec_name, char *path);
char				*search_path(t_envp *envp_list);
char				**convert_envp(t_envp *envp_list);
t_envp				*search_envp_key(t_envp **envp, char *key);

void				init_envp(t_envp **envp_list, char **envp);
void				print_envp(t_envp *list);
void				add_cmd_node(t_cmd *new_node, t_cmd **cmd_lst,
						t_tab **global, t_envp **envp);

/*Minishell freeing memory*/
void				free_tab(void **my_tab);
void    			free_everything(t_token **token, char *prompt);
void				free_envp(t_envp **list);
void				free_cmd_list(t_token **token_lst);

char				*get_prompt(t_envp *envp_list);
void				ft_signal(void);
char				*ft_strchr_reverse(char *s1, char c);

/*builtins*/
void				ft_export(t_envp **envp_list, char *key_value);
void				ft_cd(t_token *token, t_envp **envp, char *path);
int					search_builtins_child(t_token *token, t_envp *envp_list);
int					search_builtins_token(t_token *token, t_envp *envp_list);
/*SIGNAL*/
void				handler(int signal);
void				init_signal(void);

void				search_key_and_replace_it(t_envp **envp, char *key,
						char *value);
char				*get_key(t_envp **envp, char *key);
/*CD*/
void				ft_add_pwd_node(t_pwd **pwd_lst, t_pwd *node);
void				init_pwd_w_envp(t_envp **envp, t_pwd **pwd_lst);
int					nbre_node(t_pwd **pwd_list);
void				remove_last_node_pwd(t_pwd **pwd_list);
void				remove_slash(t_pwd **pwd_node);
void				absolute_path(char *path, t_envp **envp);
char				*remove_backslash_at_end(char *pwd);
void				free_pwd_lst(t_pwd **pwd);
void				home_path(char *path, t_envp **envp);
int					testing_absolute_path(char *path, t_envp **envp);
void				method_of_list(char *path, t_pwd *new_node, t_envp **envp);
char				*search_value_envp(t_envp **envp, char *key);
void				parse_pwd(t_pwd **pwd_lst, char *pwd_value);
int					is_symbolic_link(const char *path);
void				remove_backslash_end(char **path);
int 				go_old_pwd(t_envp **envp);
void				ft_cd_add_slash(char *tmp, t_pwd *new_node);
int					ft_chdir(char *path);
char				*pwd_until_slash(char *pwd);
/*PWD*/
void				print_env_export(t_envp **envp);
void				ft_pwd(t_envp *envp_list);
/*UNSET*/
void				ft_unset(t_envp **envp, char *key_to_remove);
/*EXIT*/
void				ft_exit(t_token *token, char *val);
/*ECHO*/
void				ft_echo(char *string, bool without_ret, t_envp **envp,
						t_token *token);
/*ENVP*/
void				add_node_to_envp(t_envp **list, t_envp *new_node);
void				increment_shlvl(t_envp **envp);
#endif