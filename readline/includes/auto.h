/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 11:50:57 by aariss            #+#    #+#             */
/*   Updated: 2020/01/28 17:09:13 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTO_H
# define AUTO_H
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include "readline.h"
# include "colors.h"

typedef struct	s_names
{
	char			*name;
	int				col;
	int				row;
	int				pos;
	int				active;
	struct s_names	*next;
}				t_names;

typedef struct	s_sugg
{
	struct s_names	*names;
}				t_sugg;

typedef struct	s_draw
{
	int				i;
	int				j;
	int				t;
	int				col;
	int				max;
}				t_draw;

typedef struct	s_autocmp_draw
{
	int		i;
	int		j;
	int		d;
	int		l;
	int		len;
}				t_autocmp_draw;

/*
 ** page sort;
*/

t_names			*sort_list_ascci(t_names *names);

/*
 ** page display_and_move;
*/

void			move_in_modes(t_line *line, int max, int col, int t);
void			free_head_to_scroll(t_line *line);
void			move_in_modes_normal(t_line *line, int max, int col, int t);
void			display_sugg_move(t_line *line);

/*
 ** page display;
*/

void			prepare_space_to_display(int t, t_line *line);
void			display_sugg(t_line *line);
int				display_name(char *str);
char			*color(char *name);
void			pos_curs_correctly(t_line *line);

/*
 ** page displaytmpstr;
*/

char			*join_two_chars(char *str, char *tmp, int n);
void			pos_curs_correctly2(t_line *line);
int				count_lines_str(t_line *line);

/*
 ** page generale;
*/

int				maxlen(t_names *names);
int				count_sugg(t_names *names);
int				count_list(char **str);
void			print_prompt1(char *prompt);

/*
 ** page get_suggestion;
*/

t_names			*get_one_sugg(char *str, char *ground);
void			get_suugestion(char *name, char *ground,\
		t_names **tmp, t_names **sugg);
int				verify_type(char *name);

/*
 ** page ground;
*/

char			*get_lastword(t_line *line);
char			*get_ground(t_line *line);
void			display_matrice(char **tmp);
char			*get_splited_word(t_line *line, char key);
void			get_ground_hint(t_line *line);
char			*min_all(char *s1);
char			*replace_tilde(char *ground, char *home);
void			get_ground_hint_four(t_line *line, char *ground);

/*
 ** page move in tab;
*/

void			move_tab(t_line *line, t_names *sugg);
void			display_str_tmp(t_line *line, int buff);
void			display_line_tmp(t_line *line);
void			clean_window(t_line *line);
void			move_tab_bus(t_line *line, char *name);
void			move_tab_tree(t_line *line, int k);
t_names			*after_check(t_line *line, t_names *sugg, t_names *tmp);

/*
 ** page quit auto mode;
*/

void			quit_mode_auto(t_line *line);
void			free_mode_auto(t_line *line);
void			free_liste_mode_auto(t_names *liste);
t_autocmp_draw	init_draw_two(t_line *line);
void			pos_curs_tab(t_line *line, char *newtmp);

/*
 ** page suggestion;
*/

t_names			*check_tab(t_line *line, t_names *sugg, t_names *tmp);
void			check_tab_and_mode(t_line *line);
t_names			*check_tab_path(t_line *line, char **paths,\
		t_names *sugg, t_names *tmp);
void			display_first_time(t_line *line);
void			check_tab_bis(t_line *l, t_names **s, t_names **t, int len);
/*
 ** page path;
*/

char			**get_path_autocmp(char *path);
t_names			*get_env_vars(t_line *line, t_names *sugg, t_names *tmp);
char			*trim_equal(char *str);

/*
 ** page free;
*/

void			free_2d(char **tmp);
void			restaur_curs(t_line *line);
int				calc_height_of_name(int len, int col);
t_autocmp_draw	init_draw(t_line *line);
t_autocmp_draw	init_draw_two(t_line *line);
t_autocmp_draw	init_draw_glob(t_line *line);

#endif
