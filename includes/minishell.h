/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:11:16 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/22 16:38:16 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <string.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include <limits.h>

# define BUILTINS	"echo:cd:pwd:export:unset:env:exit"
# define PROMPT_START "🔥💀🔥"
# define SKULL	"💀"
# define FLAME	"🔥"
# define PATH_TO_TMP	"/tmp/"
# define BLUE_BOLD "\e[1;34m"
# define GREEN_BOLD "\e[1;32m"
# define MAG_BOLD "\e[1;35m"
# define RED_BOLD "\e[1;31m"
# define UNSET "\033[0m"

// General macros

# define OK			1
# define KO			0

// Redirection macros

# define DOUBLE 	2
# define SINGLE		1
# define OUTPUT		1
# define INPUT		0

// Hdoc_utils_macros

# define START		0
# define END		1

// parse macros

# define ARGUMENT	0
# define FULL_LINE	1

// signal/shell status macros

# define ON_READ		0
# define ON_HDOC		1
# define ON_EXE			2

// Export macros

# define NOTDEFINED		0
# define DEFINITION		1
# define REDEFINITION	2
# define EXPORT_ERROR	3
# define EXPORT_CALL	1
# define NOT_EXPORT		0

// $? related macros

# define Q_MARK_KO		0
# define Q_MARK_OK		1

// exe macros

# define IN				0
# define OUT			1
# define CHILD			0
# define FATHER			1

/*Process node structure*/
typedef struct s_nod
{
	int				p_nbr;
	char			*line;
	char			*line_aux;
	char			*line_save;
	char			*line_aux_save;
	int				fdi;
	int				fdo;
	char			**cmd;
	int				btin;
	char			*hdoc_name;
	int				n_hdoc;
	int				launch;
	struct s_nod	*next;
}					t_nod;

/*Local nvironment variable struct*/
typedef struct s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}					t_var;

/*General shell struct*/
typedef struct s_shell
{
	char	*rl;
	char	*parse_rl;
	char	*rl_tofree;
	char	*rl_aux;
	char	ac;
	char	**env;
	int		n_proc;
	t_nod	*p_lst;
	int		q_mark_err;
	t_var	*envar;
	int		status;
	int		assign_error;
	pid_t	pid;
	char	*pmt;
}				t_shell;

t_shell	*g_shell;

// inicialise

t_shell	*init_megastruct(int ac, char **av, char **env);
t_nod	*create_pnode(char **aux, char **str, int *n_proc);
t_var	*new_env_var(char *name, char *value);

// errno_outputs

int		print_errno(void);
void	multiline_error(int *q_mark_err);
void	parse_error_near(char *str, int *q_mark_err);
void	forbidden_char_found(char *str, int *q_mark_err);
void	command_not_found_error(char *cmd);
void	error_msg_relative_to_file(char *file, t_nod *node);
void	call_error(void);
void	ambiguous_redirect_error(char *name, t_nod *node);
void	error_msg(void);
void	export_error(char *arg, char *name);
void	cd_error(char *path);
void	exit_error(char *arg, int type);
void	unset_error(char *arg);

// $? utils

void	update_q_mark_variable(int new_value);
void	print_and_update(char *str, int new_value);

// signals / signal

void	ft_signal_main(void);
void	ft_signal_ctrl_c(int sig);
void	ft_signal_stop_all_process_launch(int sig);
void	ft_signal_ctrl_d_process(int sig);
void	ft_send_ctrl_c_to_child(int sig);
void	wait_childs(void);

// execute / run_command

int		ft_isbuiltin(char **args);
void	exec_builtin(char **args, int process_type);
void	clear_envar_defs(char ***cmd);
char	**clone_environment(char **env, int segmentation_fault);
char	*find_exec_path(char **cmd);
void	launch_processes(void);
void	launch_from_childs(t_nod *node, int i);
void	open_hdoc_fd(t_nod *node);
void	close_all_fds(t_nod *node);
void	dup_stdin_stdout_and_close(int new_in, int new_out);
void	call_execve(t_nod *node);
void	wait_and_get_q_mark(void);
void	replace_value_on_local_env(t_var *nod, char *name, char *val);
t_var	*new_env_var(char *name, char *value);
int		check_if_def(char *str);

// builtins

void	ft_echo(char *argv[]);
void	ft_env(int mode);
void	ft_exit(char **args, int type);
void	ft_pwd(void);
void	ft_cd(char *str);
void	ft_export(char **argv);
void	ft_unset(char **av);
int		len_name(char *str);
int		find_env(char *word);
void	add_to_global_env(char *name, char *value, int stat);
void	check_for_local_value(char *name, char **prev_value);

// error control parser fts

int		initial_parser(void);
int		comma_parser(char **str, int *q_mark_err);
int		redirection_pipe_parser(char **str, int *q_mark_err);
void	process_command_parsing(void);

// redirection related

void	heredoc_piece(void);
char	*hdoc_filename(int reset);
char	*eof_gatherer(char **line, int *n_hdoc);
void	other_io_redirections(void);
void	clean_other_hdoc(t_nod *node);
void	rebuild_aux_strings(t_nod *node);
void	do_redirection(t_nod *node, char **aux, int red, int red_io);
char	*filename_gatherer(char **str, t_nod *node);

// command argument gathering related

void	gather_process_arguments(void);
void	add_envar_len(int *len, char *str, int full_line);
void	write_str_w_envar(char **line, char **fname, int *len, t_nod *node);
void	expand_vars_outside_strings(t_nod *node);

// STRING PRESTIDIGITATION

void	place_str_pointers(char **aux, char **str_blnk, char **str_f, int i);
void	edit_string(char **str, int *i, int envar);
int		string_length_bash(char *str, int envar);
void	move_str_pointers(char **str, char **aux, int i);

// free  functions

void	free_process_list(void);
void	free_matrix(char **matrix);
void	free_two_ptrs(void *s1, void *s2);
void	free_three_ptrs(void *s1, void *s2, void *s3);
void	free_four_ptrs(void *s1, void *s2, void *s3, void *s4);
void	unlink_all_heredocs(void);
void	unlink_one_heredoc(char **hdoc_name);

// env search related functions

char	*get_var_name(char *str);
char	*get_var_value(char *name, int call_stat);
int		ft_isvalid_env_start(char a, int consider_q_mark_err);
int		ft_isvalid_env_core(char a);
void	add_to_local_env(char *name, char *value);
int		check_if_def(char *str);
char	*check_env(char *name);
void	overwrite_env_value(char *name, char *value);

// debug

void	print_all_pointers_in_structs(void);

#endif
