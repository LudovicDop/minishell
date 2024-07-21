/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldoppler <ldoppler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:11:00 by ldoppler          #+#    #+#             */
/*   Updated: 2024/07/21 16:40:01 by ldoppler         ###   ########.fr       */
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

typedef struct s_id
{
	pid_t		id;
	struct s_id	*next;
}	t_id;

typedef struct s_glob
{
	t_lexer	*root;
	t_envp	*envp;
	t_id	*id_node;
	int		fd_in_old;
	char	*prompt;
}	t_glob;

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
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strchr2(const char *s, int c);
char	*search_and_replace(char *s, char c_to_rplce, char *insert);
int		how_many_cmd(t_lexer *token);

/*Minishell main function exec*/
void	ft_error_exec(char *error_msg, char *cmd_name);
int		execute_command(t_lexer *t, int *pipe_fd, t_envp *envp_list, t_glob *g);
int		execute_ast(t_lexer *node, int pipe[2], t_envp **envp_list, t_glob *g);
int		ft_redirection(t_lexer *node, int *p_fd, t_glob *g, t_envp *envp_list);
void	execute_fail(t_glob *glob, t_lexer *t, t_envp *envp_list, int *p_fd);

/*Minishell parsing*/
int		empty_after_symbol(char *input_cmd);

/*Minishell search good path in envp*/
void	ft_env(t_envp **envp_list);
char	*test_good_path_for_exec(char *exec_name, char *path);
char	*search_path(t_envp *envp_list);
char	**convert_envp(t_envp *envp_list);
// t_envp				*search_envp_key(t_envp **envp, char *key);

void	init_envp(t_envp **envp_list, char **envp);
void	print_envp(t_envp *list);

/*Minishell freeing memory*/
void	free_tab(void **my_tab);
void	free_everything(t_lexer **token, char *prompt);
void	free_envp(t_envp **list);
void	free_cmd_list(t_lexer **token_lst);
void	free_lexer(t_lexer *lex);
char	*get_prompt(t_envp *envp_list);
void	ft_signal(void);
char	*ft_strchr_reverse(char *s1, char c);

/*builtins*/
void	ft_export(t_envp **envp_list, char *key_value);
void	ft_cd(t_lexer *token, t_envp **envp, char *path);
int		search_builtins_child(t_lexer *token, t_envp *envp_list);
int		search_builtins_token(t_lexer *token, t_envp **envp_list, t_glob *glob);
/*SIGNAL*/
void	handler(int signal);
void	init_signal(int choice);
void	reset_signal(void);
void	handler_heredoc(int sig);

void	search_key_and_replace_it(t_envp **envp, char *key, char *value);
char	*get_key(t_envp **envp, char *key);
/*CD*/
void	ft_add_pwd_node(t_pwd **pwd_lst, t_pwd *node);
void	init_pwd_w_envp(t_envp **envp, t_pwd **pwd_lst);
int		nbre_node(t_pwd **pwd_list);
void	remove_last_node_pwd(t_pwd **pwd_list);
void	remove_slash(t_pwd **pwd_node);
void	absolute_path(char *path, t_envp **envp);
char	*remove_backslash_at_end(char *pwd);
void	free_pwd_lst(t_pwd **pwd);
void	home_path(char *path, t_envp **envp);
int		testing_absolute_path(char *path, t_envp **envp);
void	method_of_list(char *path, t_pwd *new_node, t_envp **envp);
char	*search_value_envp(t_envp **envp, char *key);
void	parse_pwd(t_pwd **pwd_lst, char *pwd_value);
int		is_symbolic_link(const char *path);
void	remove_backslash_end(char **path);
int		go_old_pwd(t_envp **envp);
void	ft_cd_add_slash(char *tmp, t_pwd *new_node);
int		ft_chdir(char *path);
char	*pwd_until_slash(char *pwd);
/*PWD*/
void	print_env_export(t_envp **envp);
void	ft_pwd(t_envp *envp_list);
/*UNSET*/
void	ft_unset(t_envp **envp, char *key_to_remove);
/*EXIT*/
void	ft_exit(t_lexer *token, char *val, t_glob *glob);
/*ECHO*/
void	ft_echo(char *string, bool without_ret, t_envp **envp, t_lexer *token);
/*ENVP*/
void	add_node_to_envp(t_envp **list, t_envp *new_node);
void	increment_shlvl(t_envp **envp);
/*REDIRECTION*/
void	ft_red_out(t_lexer *token, bool is_cmd);
void	ft_red_append(t_lexer *token, bool is_cmd);
int		ft_red_in(t_lexer *token);
int		ft_heredoc(t_lexer *node, int *p_fd, t_glob *g, t_envp *envp_list);
/*linked list for fork pid_t*/
void	ft_add_lst_id_node(t_id **id_node, pid_t new_id_value);
void	ft_free_id_list(t_id **my_list);
/*minishell exec_bis*/
int		ft_end_cmd(t_lexer *node, t_glob *glob, int *pipe_fd);
void	ft_wait_everyone(t_glob *glob);
int		ft_first_node_init(t_lexer *node, t_glob *glob, int *pipe_fd);
int		ft_single_cmd(t_lexer *node, t_glob *g, int *p_fd, t_envp **envp_list);
t_lexer	*ft_skip_to_next_cmd(t_lexer *node);
void	ft_heredoc_signal(void);
void	ft_heredoc_free(t_lexer *node, t_glob *glob, bool end);
int		ft_empty_after_heredoc(t_lexer *node);
void	ft_norm(int *pipe_fd, char *tmp, char *full_string);
int		ft_is_it_pipe(t_lexer *root);
void	execute_fail_builtins(t_glob *g, t_lexer *t, t_envp *e_lst, int *p_fd);
#endif
