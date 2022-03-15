/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 12:04:27 by aariss            #+#    #+#             */
/*   Updated: 2020/02/17 15:38:50 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H
# include "libft.h"
# include "bolean.h"
# include "parsin.h"
# include "get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <assert.h>
# include <fcntl.h>
# include <stdio.h>
# include <termios.h>
# include <term.h>
# include "hash.h"
# include <termios.h>
# include <term.h>
# include "../../readline/includes/history.h"

/*
** metacharacters
*/

# define BACKSLACH '\\'
# define SQUOTE '\''
# define DQUOTE '"'
# define HASH '#'
# define PIPE '|'
# define BACKGROUND_AND -12
# define AND -13
# define OR -14
# define SEPERATOR -3
# define HEREDOC -19
# define COLOR2 "\e[35m"
# define RESET2 "\e[39m"
# define P_CHECK (ft_strcmp(h->lst->cmd[1], "-P"))
# define L_CHECK (ft_strcmp(h->lst->cmd[1], "-L"))
# define MAD_DECLARE(type, x,y) type x=y

/*
** DATASTRUCTURES;
*/

typedef struct stat			t_stat;
typedef	struct s_hash		t_hash;
typedef struct s_env		t_env;
typedef struct s__mc		t__mc;
typedef	struct s_var		t_var;
typedef	struct s_info		t_info;
typedef	struct s_cmd		t_cmd;
typedef	struct s_index		t_index;
typedef	struct s_quote		t_quote;
typedef	struct s_holder		t_holder;
typedef	struct s_childs		t_childs;
typedef struct s_alias		t_alias;
typedef struct s_expansion	t_expansion;
typedef struct s_group		t_group;
typedef struct s_process	t_process;
typedef struct s_message	t_message;
typedef struct s_varss		t_varss;
typedef struct s_tmp_env	t_tmp_env;

/*
** ENVIRONEMENT;
*/

struct		s_env
{
	char			*var;
	char			*value;
	int				env;
	char			*value_copy;
	struct s_env	*next;
};

/*
** PRE_PARSE LIST;
*/
struct		s__mc
{
	char			**cmd;
	int				def;
	struct s__mc	*next;
};

/*
** QUOTE HANDLER IN RECALL READLINE;
*/

struct		s_var
{
	int		a;
	int		b;
	int		c;
	int		d;
	int		index;
};

/*
** MAIN LIST;
*/

struct		s_info
{
	char			*file;
	int				sfd;
	int				dfd;
	int				read_meth;
	struct s_info	*next;
};

struct		s_cmd
{
	char			**cmd;
	struct s_info	*red;
	struct s_cmd	*next;
};

/*
** QUOTING STRUCT FOR PARSIN;
*/

struct		s_index
{
	int		i;
	int		j;
	int		v;
};

struct		s_quote
{
	int		keeper;
	int		definer;
	t_env	*env;
};

/*
** PROCESS
*/

struct		s_group
{
	char		*cmd;
	int			id;
	pid_t		pgid;
	int			current;
	t_bool		suspend;
	t_process	*process;
	t_group		*next;
};

struct		s_process
{
	char		*cmd;
	pid_t		pid;
	t_bool		suspend;
	int			status;
	t_process	*next;
};

struct		s_message
{
	char		*message;
	t_message	*next;
};

struct		s_varss
{
	int		i;
	int		j;
	char	c;
	int		x;
	char	**argv;
	t_env	*env;
	char	*cmd1;
	char	*cmd2;
	char	**tableau;
	t_env	*current;
	t_env	*prev;
	char	*str;
	t_env	*new;
	char	**key_val_split;
	char	*key_val;
};

/*
** DATA STRUCTURE HOLDER;
*/

struct		s_holder
{
	t_env			*head_ref;
	t_list			*tmp_env;
	t__mc			*mclst;
	t__mc			*current_mclst;
	t_cmd			*lst;
	char			*line;
	char			*tempo_line;
	char			*linecpy;
	int				linecpyflag;
	char			*heredoc;
	char			*ptr;
	char			*stctmp;
	char			*tmp;
	int				hdocflg;
	int				last_status;
	t_bool			background;
	t_bool			force_exit;
	char			*error;
	t_message		*messages;
	t_group			*current_groupe;
	t_bool			pipe_exist;
	pid_t			pid_42sh;
	int				fd;
	int				fd_0;
	int				fd_1;
	t_bool			interactive;
	t_bool			reset_readline;
	t_bool			ctrl_check;
	t_group			*groups;
	t_alias			*aliases;
	t_hash			hash;
	t_all_hist		*history;
	t_bool			test;
	struct termios	term;
};

/*
** CHILDS_LIST;
*/

struct		s_childs
{
	pid_t			child;
	int				index;
	struct s_childs	*next;
};

/*
** parameter_expansion
*/

struct		s_expansion
{
	int		value_len;
	char	*token;
	char	*parameter;
	char	*value;
	char	*word;
	char	*symbol;
	char	*final_string;
	char	**val1;
};

/*
** ALIAS LIST;
*/

struct		s_alias
{
	char			*alias;
	char			*original;
	struct s_alias	*next;
};

/*
** ENV TMP LIST;
*/

struct		s_tmp_env
{
	int		i;
	t_env	*my_env;
	int		is_tmp;
	int		command_status;
};

/*
** PARSIN;
*/

char		*parsin(t_holder *h);
void		sys_call(t_holder *h, struct termios term);
char		*token_manager(char *str, char *line, int *i);
char		*escape_character(char *str, char *line, int *i, t_quote q_r);
char		*ignore_quote(char *line, int pick);
void		add_file(t_cmd **lst, t_info **head, char **cmd, t_index *l);
void		add_casual(t_cmd **lst, t_info **head, char **kratos, t_index *l);
char		*error_assembly(int fd);
t_info		*create_info(char *kratos, char *file, t_index *l, t_index def);
t__mc		*mc_maker(t_holder *h);
t_cmd		*last_splice(char **data, t_env *env, t_alias *alias);
int			syntax_error(char *line);
char		**rip_quotes(char **cmd);
char		*dollar_parenthesis(t_holder *h, char *str, int *i);
void		seperators_parse(char *line, char **str, int *i);
int			seperators_check(char c, char d);
char		*trap_lbeldi(char *str);
char		*look_elsewhere(char *line, int *i, char *str);
int			quote_skipper(char *line, int i);
char		*adjust_curly_line(char *line);
int			count_expansion_curly(char *line);
char		*voidyx(int *fd, int *keeper, char *xtr, t_holder *h);
char		*subshell_parser(char *line, int *i);
void		adjust_line(t_holder *h, int *i);
char		*newline_tospace(char *line);
t_bool		parse_error_check(t_holder *h);
char		*kill_one(char *line, char c);
t_bool		is_empty(char *line);
int			just_spaces(char *line);
int			count_or(char **line, int *how_many);
int			count_and(char **line, int *how_many);
int			coma_trickster(char **line);
void		verify_error(char *termtype, int s);
int			weird_tokens(char **line);
int			token_mapper(char *line);
int			token_scout(char *line);
int			pipe_scout(char *line);
void		skippy(char **line);
t_bool		cmd_list_check(t_cmd *lst);
char		*current_dir_manager(t_holder *h);
int			hash_manager(t_holder *h, int i);
int			fc_manager(t_holder *h, int status);
void		verify_error(char *termtype, int s);
char		*no_more_space(char **line);

/*
** alias
*/

t_alias		*set_alias(t_alias *alias, char *name, t_alias *end);
int			edit_alias(t_alias **alias, char *name);
void		unalias(t_alias **alias, char *name);
t_alias		*tail(t_alias *alias);
void		list_aliases(t_alias *lst);
t_alias		*init_aliases();
char		**ft_shell_strsplit(char const *s, char c, char *confirm);
t_alias		*create_alias_element(char *alias, char *original);
int			alias_manager(t_holder *h);
char		*ft_strchr_quoted(const char *str, int c);
char		**do_your_bloody_work(char **cmd, t_alias *alias);
int			print_one_alias(t_holder *h, t_alias *aliases);
int			check_unalias(char **cmd, t_alias **alias);
void		alias_parse(t_holder *h);
void		free_alias_vars(char *a, char *b, char *c);
void		free_list_alias(t_alias *head);

/*
** COUNT;
*/

int			count_arg(char **cmd);
int			count_mclst(t__mc *lst);
int			count_lstgod(t_cmd *lst);
int			len_of_list(t_env *current);
int			count_accurance(char *str, char c);
int			count_accurance_unquoted(char *str, char c);
int			count_accurance_unquoted(char *str, char c);
int			count_subshell_parenthesis(char *line);

/*
** CHECK;
*/

int			ultimate_check(char *kratos);
int			ft_iswhite(char c);
int			got_no_token(char *kratos);
int			is_a_builtin(char *cmd);
int			check_red(t_info *lst);
int			just_spaces(char *line);
int			cmd_is_found(char **tab1, char **ptrcmd, char *temp);
int			syntax_checker(char *line);

/*
** $ FUNCTIONS PARSIN;
*/

char		*dollar_get_simple(char *name, t_env *env, char **ptr);
char		*dollar_get_quoted(char *name, t_env *env, char **ptr);
char		*dollar_handle_simple(char *toto, char *line, int *i, t_env *env);
char		*dollar_handle_quoted(char *toto, char *line, int *i, t_quote sp);
char		*dollar_curly(char *cmd, char *str, int *i, t_env *env);
void		skip_alpha(char *line, int *i);

/*
** SHELL FUNCTIONS;
*/

char		*fromfd_tofile(int fd_zero);
void		shell(t_holder *h);
void		child_pid(char **command, t_holder *h, pid_t *get, t_bool use_hash);
void		print_lstra(t_cmd *lst);
int			retrieve_the_digit(char *name, int	delimiter);
int			darlin_g(t_holder *h);
int			deathly_hallows(t_info *lst);
t_childs	*create_child(pid_t child_pid, int *t, int def);
int			kill_pid(t_holder *h, int *keeper, int status);
void		cheap_trick(int *keeper, int trick);
void		sys_cmd(char **command, char *path_found, pid_t *get, t_holder *h);
void		execute(char **command, char *path_found, pid_t *get, t_holder *h);
char		**get_env(t_env **head_ref);
int			builtin_cmds(t_holder *h, int j, t_bool exit_after);
int			builtin_cmds_1(t_holder *h, int j, int i);
void		which_cmd(char *arg, t_env **head_ref);
int			own_commands(char **cmd);
void		del_node(char *s, t_env **head_ref);
void		add_node_1(t_env *curr, t_env *new_node);
void		echo_cmd(char *arg, char *narg, int flag);
int			specialchar(char *s);
void		ft_chdir(char *path, char *cwd, t_env **head_ref, int flag);
void		swap(t_env **head_ref, char *lastcwd, char *cwd);
void		reset_fds(void);
char		*get_var(char *deli, t_env **head_ref);
void		print_env(t_env **head_ref);
t_env		*copy_of_env(char **tab1);
void		history_terminator(t_holder *h);
void		createlist(t_env **head_ref, t_env **tail, char *var);
char		**get_path(t_env **head_ref);
int			find_path(char *penv);
void		signal_handler(int sign);
int			ft_cd(t_holder *h);
int			ft_echo(t_holder *h);
int			ft_exit(t_holder *h, int *x);
void		shell_execute(t_holder *h, int count);
void		heredoc(char *line, int start, int *i, char **str);
void		error_monkey(t_cmd **lst);
char		*assemble_path(char *current, char *path);
char		*cd_with_flag(t_holder *h, char *new_dir_path);
char		*chdir_path(t_holder *h, int flag, int *t);
char		*chdir_or_errno(t_stat buf, char **cmd, int flag, t_env *env);
char		*chdir_with_flag(t_holder *h);
int			is_flag(char *str);
int			swap_paths(t_env **env);
void		update_env(char *new_path, char *old_path, t_env **env);
char		*rip_whites(char *cmd);
char		**rip_quotes(char **cmd);
void		white_broker(char **str, char **cmd);
void		exit_bastard(t_holder *h, int status);
int			is_escape_white(char c);
int			count_special_case(char *line, char token);
void		and_and_counter(char *line, int *i, int *len, int *count);
int			avoid_quote(char *line, int i, int param);
int			which_and_del(t_holder *h, int j);
char		*verify_env(char *arg, t_env **head_ref);
void		ft_export_declare(t_env **head_ref, char *key_val,
	t_bool global, t_bool force);
int			aggregation_fd(t_info *lst, t_bool def);
void		display_error(int fd);
int			hash_env_rest_treat(t_holder *h, t_tmp_env *x);
void		add_env_tmp(t_env **head_ref, t_list *lst,
	t_bool global, t_bool force);

/*
** - Gestion Error;
*/

void		env_gerror(int flag);
int			error_cases(char **arr);
void		chdir_gerror(char *path, int flag);
void		path_gestion_error(char *path);

/*
** readline and recall of readline;
** heredoc and quotes functions;
*/

int			metacharacters(char ch, int flag);
int			heredoc_handler(t_holder *h, char **line);
int			meta_handler(char *line, int *flag);
int			get_len_before_heredoc(char *str, int counter);
int			get_len_of_needle(char *s);
char		*heredoc_new_line(char **tmp, char **line);

/*
** FREE;
*/

void		free_structure(t_holder *h, int flag);
void		free_list_mc(t__mc *lst);
void		free_list_env(t_env **head_ref);
void		free_main_lst(t_cmd *lst);
void		free_child(t_childs *lst);
void		free_heredoc_helper(char *needle, char *s);
char		*readline(char *str);

/*
** set envs
*/

int			len_of_var(char *s);
int			ft_setvariables(t_holder *h, int i, char **arg);
void		print_export(t_env **head_ref, char **token);
int			ft_export(char **token, t_holder *h);
void		ft_set(t_holder *h);
t_env		*copy_env(t_env *env);
void		export_variables(t_env **head_ref, char **token);
void		print_exp(t_env *env, int i);
void		print_export(t_env **head_ref, char **token);
char		**splite_env(char const *s);
int			check_set(char *cmd);
char		*replace_espace(char *value1);
void		ft_putvalue(char *value);
int			export_option(char **args, int *option, int *index);
void		ft_print_export(t_env *head_ref);
t_env		*ft_find_decalarion(t_env *head_ref, char *key);
void		ft_export_declare2(t_varss *v, t_env **head_ref, t_bool global);

/*
**	ft_type
*/

void		ft_type(t_holder *h, char **cmd);

/*
**	Parameter Expansion
*/

char		*parameter_expansion(char *token, t_env *env);
void		minus(t_expansion *exp);
void		egale(t_expansion *exp, t_env *env, char *kv);
int			check_env_in(char *key, t_env *env);
void		colon_question(t_expansion *exp);
void		question(t_expansion *exp);
void		plus(t_expansion *exp);
void		double_modulo(t_expansion *exp);
void		modulo(t_expansion *exp);
void		double_hashtag(t_expansion *exp);
void		hashtag(t_expansion *exp);
int			skip_quotes(char *str);
int			check_parameter_expansion(char *arg);
char		*dollar_doer(char *cmd, t_env *env);
char		*fromfd_tofile(int fd_zero);
int			exit_status_expansion(int i);
int			is_toset(char *str);
int			is_match_rev(char *str, char *in, int i, int j);
int			is_match(char *str, char *in, int i, int j);
void		get__expansions(t_expansion *exp, t_env *env);
void		get_parameter(t_expansion *exp, int len, int i);
void		check_symbols(t_expansion *exp, int *i);
void		free_exp(t_expansion *exp);
int			parameter_errors(t_expansion *exp);
void		do_symbol(t_expansion *exp, t_env *env);
int			check_exp_token_end(char *token, int i, int len);
int			check_operators(char c);
t_env		*copy_env(t_env *env);
int			check_set(char *cmd);
int			ft_str_isdigit(char *str);

/*
** MYAMANI V1
*/

int			to_reset_hash(int i);
int			temporaire_variable(int i);
int			not_valid_identifier(char *token, int j, int q);

/*
** commands Handler **
*/

t_holder	*get_set_holder(t_bool set, t_holder **h);
void		command_handler(t_holder *h, t_bool same_groupe);
int			eval_command(t_holder *h, char **data);
void		prepare_shell(t_holder **h, char **environ);
pid_t		execute_handler(char *cmd, char **args, char **env, t_holder *h);
void		process_signal(int sig);

/*
** fc **
*/

int			ft_fc(char **cmd, t_all_hist *history, t_env *env_lst, t_holder *h);
void		execute_fc(t_holder *h, t_bool	background);

/*
** process & groups
*/

void		show_messages(t_message *message);
void		join_group(t_group *group, pid_t pid, t_bool suspend, char *cmd);
void		create_group(t_holder *h, pid_t pgid, char *cmd);
t_bool		process_status(t_process *process,
			t_bool wait_res, t_bool status_anyway);
void		delete_process(t_group *group, t_process *prev,
			t_process *node, pid_t pid);
int			monitor_process(t_group *group, t_process *process,
			t_bool wait_res, t_bool status_anyway);
int			groups_ids(t_group *group, int start_id);
void		delete_group(t_holder *h, t_group *prev, t_group *node, pid_t pgid);
void		monitor_groups(t_holder *h);
t_bool		show_groups(t_group *group, int id, int flag);
t_bool		resume_group_fg(t_holder *h, t_group *group, int id);
t_bool		resume_group_bg(t_holder *h, t_group *group, int id);
char		*ft_strsignal(int sig);
int			valid_id(char *id);
void		print_valhala(t_cmd *valhala);
int			fg_handler(t_holder *h, char *args);
int			fg(t_holder *h, char **args);
int			bg_handler(t_holder *h, char **args, int status);
int			bg(t_holder *h, char **args);
int			check_flag(char **args, char *head, char *message, t_bool use_flag);
int			show_jobs_msg(char *cmd, char *flag);
int			show_jobs(t_holder *h, char **args, int flag, int status);
int			jobs(t_holder *h, char **args);
t_bool		is_aand_oor_exist(t__mc *root);
t_bool		is_and_exit(t__mc *root);
void		default_signal(void);
t__mc		*and_or_handler(t_holder *h, t__mc *group,
	t_bool execute, t_bool exit_after);
t_bool		is_and_exit(t__mc *root);
t_bool		is_aand_oor_exist(t__mc *root);
t_bool		is_operator(int command);
void		group_state(t_group *group, pid_t pgid);
void		group_state(t_group *group, pid_t pgid);
t_bool		is_process_suspended(t_process *process);
void		show_process(t_process *process);
void		add_message(t_group *group, t_process *process, t_bool suspend);
void		set_signals(void);
void		ft_tcsetpgrp(int fd, pid_t pgid);
pid_t		ft_tcgetpgrp(int fields);
void		env_val_copy(t_env *head_ref);
void		env_diff(t_env **head_ref, t_env *prev, t_env *head);
void		extract_env(t_holder *h);
void		del_env(t_env **head_ref, t_env *prev, t_env *node, char *key);
#endif
