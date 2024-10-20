/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:11:00 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/30 20:09:16 by ldoppler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../srcs/minishell_parsing/includes/final_lexer.h"
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
# define PATH_DEF \
	"PATH=/usr/local/sbin:/usr/local	\
/bin:/usr/sbin:/usr/bin:/sbin:/bin"

typedef struct s_id
{
	pid_t			id;
	struct s_id		*next;
}					t_id;

typedef struct s_glob
{
	t_lexer			*root;
	t_envp			*envp;
	t_id			*id_node;
	int				fd_in_old;
	// int				fd_out_old;
	char			*prompt;
	char			*input_cmd;
	t_lexer			*current_node;
	t_lexer			*last_cmd;
}					t_glob;

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

int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strjoin2(char *s1, char *s2);
char				*ft_strchr2(const char *s, int c);
char				*search_and_replace(char *string, char c_to_replace,
						char *insert);
int					how_many_cmd(t_lexer *token);
void				ft_error_exec(char *error_msg, char *cmd_name);
int					execute_command(t_lexer **t, int *p_fd, t_envp *envp_list,
						t_glob *g);
int					execute_ast(t_lexer *n, int pipe[2], t_envp **envp_list,
						t_glob *g);
int					ft_redirection(t_lexer *n, int *p_fd, t_glob *g,
						t_envp *envp_list);
void				execute_fail(t_glob *g, t_lexer *t, t_envp *envp_list,
						int *pipe_fd);

int					empty_after_symbol(char *input_cmd);

void				ft_env(t_envp **envp_list);
char				*test_good_path_for_exec(char *exec_name, char *path);
char				*search_path(t_envp *envp_list);
char				**convert_envp(t_envp *envp_list);

void				init_envp(t_envp **envp_list, char **envp);
void				print_envp(t_envp *list);
void				free_tab(void **my_tab);
void				free_everything(t_lexer **token, char *prompt);
void				free_envp(t_envp **list);
void				free_cmd_list(t_lexer **token_lst);
void				free_lexer(t_lexer *lex);

char				*get_prompt(t_envp *envp_list);
void				ft_signal(void);
char				*ft_strchr_reverse(char *s1, char c);

void				ft_export(t_envp **envp_list, char *key_value);
void				ft_cd(t_envp **envp, char *path);
int					search_builtins_child(t_lexer *token, t_envp *envp_list);
int					search_builtins_token(t_lexer *t, t_envp **e_lst, t_glob *g,
						int *p_fd);
void				handler(int signal);
void				init_signal(int choice);
void				reset_signal(void);
void				handler_heredoc(int sig);

void				search_key_and_replace_it(t_envp **envp, char *key,
						char *value);
char				*get_key(t_envp **envp, char *key);
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
int					go_old_pwd(t_envp **envp);
void				ft_cd_add_slash(char *tmp, t_pwd *new_node);
int					ft_chdir(char *path);
char				*pwd_until_slash(char *pwd);
void				print_env_export(t_envp **envp);
void				ft_pwd(t_envp *envp_list);
void				ft_unset(t_envp **envp, char *key_to_remove);
void				ft_exit(char *val, t_glob *glob, int *pipe_fd);
void				ft_echo(char *string, bool without_ret);
void				add_node_to_envp(t_envp **list, t_envp *new_node);
void				increment_shlvl(t_envp **envp);
void				ft_red_out(t_lexer *token, bool is_cmd);
void				ft_red_append(t_lexer *token, bool is_cmd);
int					ft_red_in(t_lexer *token);
int					ft_heredoc(t_lexer *n, int *p_fd, t_glob *g,
						t_envp *envp_list);
void				ft_add_lst_id_node(t_id **id_node, pid_t new_id_value);
void				ft_free_id_list(t_id **my_list);
int					ft_end_cmd(t_lexer *node, t_glob *glob, int *pipe_fd,
						t_envp **envp);
void				ft_wait_everyone(t_glob *glob);
int					ft_first_node_init(t_lexer *node, t_glob *glob,
						int *pipe_fd);
int					ft_single_cmd(t_lexer *n, t_glob *g, int *pipe_fd,
						t_envp **envp_list);
t_lexer				*ft_skip_to_next_cmd(t_lexer *node);
void				ft_heredoc_signal(void);
void				ft_heredoc_free(t_lexer *node, t_glob *glob, bool end);
int					ft_empty_after_heredoc(t_lexer *node);
void				ft_norm(int *pipe_fd, char *tmp, char *full_string);
int					ft_is_it_pipe(t_lexer *root);
void				execute_fail_builtins(t_glob *g, t_envp *e_list, int *p_fd);
void				ft_heredoc_stock_string(char **tmp, char **full_string);
char				*ft_empty_envp_prompt(char *tmp_path, char *prompt,
						char *tmp_user);
char				*init_prompt_path2(void);
void				ft_init_glob(t_glob **glob, t_lexer **token,
						t_envp **envp_list);
void				free_token(t_token *token);
void				free_lexer(t_lexer *lex);
int					ft_exit_minishell(t_glob **glob, t_envp **envp_list,
						int *pipe_fd);
void				ft_minishell_free(t_lexer **token, t_glob **glob);
void				ft_search_prompt_val(t_envp **current, char **tmp_path,
						char **tmp_user);
char				*init_prompt_user(char *tmp_user, t_envp **envp_list);
char				*init_prompt_path(char *tmp_path, t_envp **envp_list);
void				exit_free(t_glob *glob, t_envp *envp_list, int *pipe_fd);
void				ft_exit_bis(t_lexer *token, t_envp **envp_list,
						t_glob *glob, int *pipe_fd);
void				handler2(int sig);
void				handler3(int sig);
void				ft_heredoc_init_exit(void);
t_lexer				*ft_skip_heredoc(t_lexer *node);
void				ft_wait_last_cmd(t_glob *glob);
int					execute_and(t_lexer *node, t_glob *glob);
void				execute_exec(t_lexer *token, t_envp *envp_list,
						int *pipe_fd, t_glob *glob);
int					ft_and(t_lexer *node, t_glob *glob, int *pipe_fd,
						t_envp **envp);
int					ft_or(t_lexer *node, t_glob *glob, int *pipe_fd,
						t_envp **envp);
void				ft_change_signal_exit(int sig);
t_lexer				*skip_until_next_symbol(t_lexer *node);
int					ft_heredoc_ret(t_lexer *node, int *pipe_fd, t_glob *glob,
						t_envp *envp_list);
void				ft_close_norm(int *pipe_fd);
void				ft_heredoc_normmm(t_glob *glob);
void				ft_echo_bis2(char *tmp, t_lexer *token, int i);
char				*ft_echo_merge(char **string);
#endif
