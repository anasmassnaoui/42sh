/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 11:59:13 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/14 21:58:55 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <stdio.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "get_next_line.h"
# include "history_struct.h"
# include "../../shell/includes/shell.h"
# define UP 4283163
# define DOWN 4348699

char					*up_history(t_all_hist *history);
char					*up_key(t_all_hist *history);
char					*nth_up(t_all_hist *history, t_history *tmp_hist);
int						count_file_lines(t_all_hist *history);
void					store_line(t_all_hist *history, char *str);
int						len_list(t_history *lst);
void					store_in_file(char *str, t_all_hist *history);
char					*down_history(t_all_hist *history);
char					*down_key(t_all_hist *history);
char					*check_in_list(char *str, t_all_hist *history);

void					double_excl(char **ptr, t_history *lst, int *t);
void					single_excl(char **ptr, t_history *lst, int *t);
void					last_of_list(char **ptr, t_history *lst, int *t);

int						check_history(int c);
t_history				*get_history(char *str);
int						count_index(char *ptr);

void					fc_command(char **str, char **cmd, t_all_hist *history,
	char **tab_env);
t_history				*reverse_lst(t_history *lst);
void					print_history(t_history *lst, int t);
char					*last_node(t_history *tmp);
char					*search_in_hist(t_history *tmp, char *ptr, int index);
char					*search_replace(char **ptr, t_history *tmp);
char					*insert_in_line(char *str, char *substr,
	int start, int end);
char					*fc_s(t_history *tmp, char **arr);
char					*middle_lst(char *str, char **arr);
void					print_index(t_history *tmp, int t, int index);
int						hist_index(t_history *tm, char *ptr);
void					print_arg(t_history *tmp, char *ptr);
void					p_lst(t_history *tmp, int t);
void					p_range(t_history *lst, int start, int end, int t);
void					p_history(t_history **hist, int t);
int						which_one(t_history *cmd, char *ptr);
void					one_arg_ln(t_history *tmp, int t,
	char **ptr, t_history *cmd);
void					many_args_ln(t_history *tmp, int t,
	char **ptr, t_history *cmd);
t_history				*copy_lst(t_history *lst);
void					fs_e_execution(char *cmd, char **flag, char **tab_env);
void					fc_e(char *ptr, char **str, char **tab_env, char *cmd);
char					*fc_e_args(t_history *tmp, char **ptr,
	t_history *cmd, char **tab_env);
char					*p_file(t_history *lst, int start,
	int end, char **tab_env);
void					in_file(t_history *lst, int fx, int start, int end);
void					fc_reverse(int t, char **ptr, t_history *cmd);
void					p_reverse(t_history *lst, int t);
void					reverse_one_arg(char *ptr, t_history *cmd, int t);
void					p_nb(t_history *cmd_tmp, int t);
void					p_rev_index(t_history *cmd_tmp, int index, int t);
void					many_args_reverse(int t, char **ptr, t_history *cmd);
void					many_args_exec(int fx, char **str);
char					*fc_s_one(t_history *tmp, char **ptr);
void					fc_ln_one(t_history *tmp, int t, char **ptr,
	t_history *cmd);
char					*fc_e_one(t_history *tmp, char **ptr,
	t_history *cmd, char **tab_env);
int						check_white_spaces(char *str);
void					shell_s(t_all_hist *history, char *prompt, char *str);
void					edit_last_node(t_all_hist *hist);
int						check_flags1(char *ptr);
void					flags1(char **str, t_history *tmp, char **ptr);
char					*flags_e_args(t_history *tmp, char **ptr,
	char **tab_env, t_history *cmd);
void					flags_e_one_arg(t_history *tmp, char **str,
	char **tab_env, char **ptr);
void					flags_e(t_history *tmp, char **ptr,
	char **str, char **tab_env);
char					*file_path();
char					*join_path(char	*ptr);
int						check_editor(char *ptr);
void					delete_file(char **tab_env);
void					store_last_cmd(t_all_hist *history, char *str);
int						check_flags(char *ptr);
void					fc_exec(t_history *tmp, char **ptr,
	char **str, char **tab_env);
char					*get_char_from_hist(t_history *lst, char *substr);
int						check_jobs(char **ptr);
void					fc_no_flags(t_history *tmp, char **ptr,
	char **str, char **tab_env);
void					free_paths(char **line, char *path1, char *path2);
void					r_in_file(char **tab_env, char *last_word);
void					free_list_hist(t_history **alst);
void					ft_free_tab2(char **p);
void					prepare_path(t_all_hist *history);

#endif
