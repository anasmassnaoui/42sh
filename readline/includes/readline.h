/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 12:12:43 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/02/14 22:37:45 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include <stdio.h>
# include <termios.h>
# include <unistd.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <fcntl.h>
# include "globing.h"
# include "history.h"
# include "../libft/libft.h"
# include "../../shell/includes/shell.h"

# define LEFT 4479771
# define RIGHT 4414235
# define DEL 127
# define DEL2 2117294875
# define OK 10
# define ALTPLUS 1130044187
# define ALTMOIN 1146821403
# define HOME 4741915
# define END 4610843
# define ALTUP 1096489755
# define ALTDOWN 1113266971
# define COPYBEFORE 10783202
# define COPYAFTER 10848738
# define ALTV 10127586
# define ALTC 42947
# define ALTS 40899
# define ALTX 8948194
# define UP 4283163
# define DOWN 4348699
# define CTRLD 4
# define CTRLL 12
# define CTRLR 18
# define TAB 9
# define CTRLR 18
# define COLOR1  "\e[45m"
# define RESET "\033[m"
# define COLOR2 "\e[35m"
# define RESET2 "\e[39m"

typedef struct			s_line
{
	char				*str;
	char				*tmp_str;
	char				*cmd;
	int					col;
	int					row;
	int					curs;
	int					in;
	int					my_in;
	char				*copy;
	int					x;
	int					msg_size;
	int					index_history;
	int					mode_select;
	char				*prompt;

	struct s_names		*names;
	char				*ground;
	char				*hint;
	int					mode_auto;
	int					tmp_curs;
	int					mode;
	int					mode_search;
	int					last_curs_pos;
	t_env				*env;
	char				*path;
	char				*home;
	int					first_time;
	int					first_auto;

	int					mode_ctrlr;
	char				*result;

}						t_line;

typedef struct			s_copy
{
	int					start;
	int					end;
	int					t;
	int					d;
	int					c;
	int					s;
}						t_copy;

typedef struct			s_vars
{
	int					i;
	int					j;
}						t_vars;

void					display_str(t_line *line, int buff);
void					*join_char(t_line *line, int buff);
char					*delete_char(t_line *line);
void					display_line(t_line *line);
void					delete_char_two(t_line *line);
void					prepare_termcap(struct termios	term);
int						my_putchar(int c);
void					verify_error(char *termtype, int s);
void					go_right(t_line *line);
void					go_left(t_line *line);
void					go_up(int col);
void					go_down();
int						verify_newline(t_line *line);
int						count_between_newlines_after(t_line *line);
int						count_last_newlines(t_line *line);
int						get_current_row(void);
int						im_in_last_col(t_line *line);
void					go_to_pos(t_line *line);
int						count_between_newlines(t_line *line);
int						count_tmp_len(t_line *line);
int						count_lines(t_line *line);
void					move_right(t_line *line);
void					move_left(t_line *line);
void					go_home(t_line *line);
void					go_end(t_line *line);
void					go_up_line(t_line *line);
void					go_down_line(t_line *line);
void					copy_mode_select(t_line *line, int i);
t_copy					get_start_end(t_line *line);
void					getcopy_select1(t_line *line, t_copy copy);
void					getcopy_select(t_line *line);
void					get_line_copy(t_line *line);
void					display_copy(t_line *line);
void					display_copy1(t_line *line, int count);
void					copy_tmp_in_str(t_line *line);
char					*copy_tmp_in_str2(t_line *line);
t_vars					initvars();
void					get_x_y(t_line *line);
void					delete_and_display_right(t_line *line);
void					delete_and_display_left(t_line *line, int x, int y);
int						get_my_col_pos(int curs, int col);
int						count_between_newlines_after2(t_line *line);
int						verify_if_exit_multiline(t_line *line);
void					cut_selection2(t_line *line, int t);
void					cut_selection3(t_line *line);
void					cut_selection(t_line *line);
char					*cut_tmp(t_line *line, int x, int y);
void					cut_part(t_line *line, int x, int y);
void					cut_selection1(t_line *line);
void					from_str_to_cmd(t_line *line, t_all_hist *history);
int						get_cote_count(t_line *line);
int						get_count_two(size_t *j, char *line, char c);
int						count_multiline(t_line *line);
void					add_line_messaage();
int						verify_if_exist_multiline(t_line *line);
t_line					initial_line(char *prompt);
int						check_arrow(t_line *line, int buff,\
		t_all_hist *history);
void					check_arrow2(t_line *line, int buff,\
		t_all_hist *history);
void					check_arrow3(t_line *line, int buff,\
		t_all_hist *history);
int						possible_to_write(t_line *line);
int						get_count_line(t_line *line);
int						my_tmp_lenght(t_line *line);
void					free_line(t_line line);
void					ctrl_r(t_line *line, t_history *lst);
void					replace_with_hist(t_line *line, t_history *lst);

int						get_escape(t_line *line);
void					get_en_rl(t_line *line, t_env *env);
char					**get_envv(t_env *head_ref);
int						len_listt(t_env *lst);
void					clear_window(t_line *line);
void					print_prompt(char *prompt);
void					history_part(t_line *line, t_all_hist *history);
void					display_history_up(t_all_hist *history, t_line *line);
void					display_history_down(t_all_hist *history, t_line *line);
void					init_histrory(t_all_hist *history, char *prompt);
void					prepare_path(t_all_hist *history);
char					*cmd_bis(t_line *line, t_all_hist *history,
		char *hint_cmd, char *newcmd);
void					go_to_end_line(t_line *line, int buff);
t_line					*get_set_line(int i, t_line *l);
void					winresize(int sig);
void					signals_bis(t_line *line);
int						signals(t_line *line);
int						verify_newline_left(t_line *line);
void					go_left_2(t_line *line);
int						ctrl_d(t_line *line, int buff);
int						ctrl_d_handler(t_line *line);
/*
** --------ctrl-r
*/

void					prepare_cntr_r(t_line *line);
void					display_ctrr_search(t_line *line, char *tmp_line);
void					select_a_letter(char *str, char c);
void					display_ctrl_result(t_line *line, char *result);
void					quit_ctrlr_mode(t_line *line, char *result);
#endif
