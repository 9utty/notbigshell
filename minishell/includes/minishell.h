/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 23:13:17 by gulee             #+#    #+#             */
/*   Updated: 2022/08/31 17:43:15 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_std
{
	STDIN_E,
	STDOUT_E,
	STDERR_E
}	t_std;

typedef enum e_type
{
	TOKEN_E,
	BLANK_E,
	REDIR_E,
	CMD_E,
	HDOC_E,
	PIPE_E = '|',
	LESS_E = '<',
	GREAT_E = '>',
	SQUOTE_E = '\'',
	DQUOTE_E = '\"'
}	t_type;

typedef enum e_bool
{
	FALSE_E,
	TRUE_E
}	t_bool;

typedef struct s_hdoc
{
	int				fd;
	char			*hdoc_name;
	char			*eof;
	struct s_hdoc	*next;
}					t_hdoc;

typedef struct s_file
{
	int	open_stdin;
	int	open_stdout;
	int	origin_stdin;
	int	origin_stdout;
}		t_file;

typedef struct s_token
{
	t_type			type;
	char			*data;
	struct s_token	*next;
}					t_token;

typedef struct s_token_table
{
	t_token	*head;
	int		token_count;
}			t_token_table;

typedef struct s_node
{
	t_type			type;
	char			*data;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

typedef struct s_tree
{
	t_node	*root;
}			t_tree;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct termios	t_termios;
typedef struct s_table
{
	t_token_table	*token_table;
	t_tree			*tree;
	t_env			*env;
	t_file			*file;
	t_termios		org_term;
	t_termios		new_term;
	int				exit_num;
	int				is_hdoc;
	int				hdoc_count;
	int				hdoc_index;
	int				is_pipe;
	int				has_pipe;
	int				is_run;
	t_hdoc			*hdoc_list;
}					t_table;

/* ======================================================
						builtin
======================================================= */
/* utils */
char			*get_key(char *str);
char			*get_env(char *str);
char			**get_av(char *str, int *ac);
char			*ft_strndup(char *str, int len);

/* ft_cd */
int				go_home(char *str, t_env *env);
void			print_cd_err(char *str);
void			renewal_pwd(t_env *env, char *pwd);
int				ft_cd(t_node *head);

/* ft_echo */
void			option_check(char **str, int *op_check);
void			print_echo(int op_check, int i, int ac, char **av);
int				ft_echo(t_node *head);

/* ft_env */
int				ft_env(t_node *head);

/* ft_exit */
int				get_ac(t_node *head);
int				digit_check(char *str);
int				get_exit_status(int ac, char *str);
int				ft_exit(t_node *head);

/* ft_export */
t_bool			ft_isdigit(char num);
int				ft_isalpha(int c);
void			print_export(t_env *env);
int				valid_argu(char *str);
t_env			*check_exist(char *key, t_env *env);
void			replace_export(t_env *tmp, char *str);
t_env			*make_new_env(char *key, char *value, char *str);
void			add_new_env(char *key, char *str, t_env *env);
void			check_argu(char **av, t_env *env);
int				ft_export(t_node *head);

/* ft_pwd */
int				ft_pwd(t_node *head);

/* ft_unset */
void			delete_node(char *key, t_env *env);
int				unset_check_exist(char *av, t_env *env);
int				ft_unset(t_node *head);

/* ======================================================
						utils
======================================================= */
/* ft */
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
char			*ft_substr(char *s, int start, int len);
char			*ft_strchr(const char *str, int c);
size_t			ft_strlen(const char *str);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(char *str);
void			*ft_memset(void *ptr, int value, size_t num);
char			*ft_itoa(int n);
int				ft_atoi(const char *str);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
char			**ft_split(const char *str, char c);
void			ft_remove(void);

/* list */
void			list_add_back(t_hdoc **list, t_hdoc *new);
t_hdoc			*list_tail(t_hdoc *list);
int				list_len(t_env *env);
char			**list_convert(t_env *env);

/* is */
t_bool			is_blank_cc(char c);

/* table */
t_table			*table_get(void);

/* signal */
void			sig_action(int sig_num);
void			set_env(char **env);

/* init */
void			init_start(char **env, int argc, char **argv);
t_tree			*init_tree(void);
t_token_table	*init_token_table(void);
t_file			*init_file(void);
t_env			*init_env(char *str);

/* termios */
void			get_org_term(void);
void			set_org_term(void);
void			echoctl_on(void);
void			echoctl_off(void);

/* main print */
void			print_main_cover(void);

/* env */
void			update_shlvl(void);
void			env_join(char **new, char *env, int *start, int *end);
char			*get_env_state(char *env);
/* error modul */
void			*null_error(const char *str);
void			error_print(const char *str);

/* env modul */
char			**first_copy_env(char **env);
char			*env_get(char *key);

/* ======================================================
						parser
======================================================= */
/* input */
t_bool			parser(char *line);

/* tree init */
t_tree			*init_tree(void);
t_node			*init_node(t_token	*token);

/* token */
void			cmd_tokenize(t_token_table **list, char *str);

/* token utils */
t_token			*token_get(t_token_table *list, int end);
void			token_add(t_token_table *token_table, t_token *new_token);

/* in utils */
void			in_pipe_hdoc(t_tree *tree, t_node *node);
void			in_redir(t_tree *tree, t_node *node);
void			in_path(t_tree *tree, t_node *node);
void			in_filename(t_tree *tree, t_node *node);
void			in_hdoc_redir(void);

/* syntax utils */
void			pipeline(int *index);
void			cmd(int *index);
void			cmd_simple(int *index);
void			redirs(int *index);
void			redir(int *index);
void			arg(int *index);
void			path(int *index);
void			filename(int *index);

/* replace utils */
void			replace(t_node *node);
void			find_end_position(char *data, int *end, int *flag);
void			join_envp(char *new, char *env, int *start, int *end);
int				join_str(char *new, char *org, int start, int end);
void			join_squote(char *rest, char *data, int *front, int *end);

/* ======================================================
						execute
======================================================= */
void			execute(t_node *node);

/* heredoc */
void			ex_heredoc(t_node *node);
t_hdoc			*hdoc_init(t_node *node);

/* pipe */
void			ex_pipe(t_node *node);

/* redir */
void			ex_redir(t_node *node);
t_bool			get_redir(void);
t_bool			close_redir(void);

/* command */
void			ex_command(t_node *node);

/* not_minishell */
void			not_minishell(t_node *node, int state);
char			**get_option(t_node *node);

/* utils */
void			exec_sig(int state);
char			**get_option(t_node *node);
#endif
