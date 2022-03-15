/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:16:25 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/02/15 17:22:12 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "auto.h"

void		check_arrow2(t_line *line, int buff, t_all_hist *history)
{
	check_arrow3(line, buff, history);
	if (buff == ALTUP)
		go_up_line(line);
	else if (buff == ALTDOWN)
		go_down_line(line);
	else if (buff == DEL || buff == DEL2)
		delete_char_two(line);
	else if (buff == ALTPLUS)
		move_right(line);
	else if (buff == ALTMOIN)
		move_left(line);
	else if (buff == ALTV)
		copy_tmp_in_str(line);
	else if (buff == ALTC)
		get_line_copy(line);
	else if (buff == ALTS)
		get_x_y(line);
	else if (buff == ALTX)
		cut_selection(line);
	else if (buff == CTRLR)
		prepare_cntr_r(line);
}

static void	check_arrow4(t_line *line, int buff, t_all_hist *history)
{
	char *tmp;

	if (line->mode_ctrlr == 1 && buff == OK)
		quit_ctrlr_mode(line, line->result);
	go_to_end_line(line, buff);
	display_str(line, buff);
	if (line->mode_ctrlr == 1 && buff != OK)
	{
		tmp = get_char_from_hist(history->lst, line->str);
		if (tmp)
		{
			ft_strdel(&line->result);
			line->result = ft_strdup(tmp);
		}
		display_ctrl_result(line, line->result);
	}
}

static int	have_to_break(t_line *line, int buff, t_all_hist *history)
{
	if (buff == OK)
	{
		line->my_in = get_current_row();
		from_str_to_cmd(line, history);
		if ((get_escape(line) == -1 || get_cote_count(line) == -1) &&
				ft_strcmp(line->prompt, "$> ") == 0)
		{
			ft_strdel(&((*line).str));
			(*line).str = ft_strdup("");
			add_line_messaage();
		}
		else
		{
			if ((*line).cmd)
				history_part(line, history);
			return (-1);
		}
	}
	return (0);
}

int			check_arrow(t_line *line, int buff, t_all_hist *history)
{
	check_arrow2(line, buff, history);
	if ((ft_isprint(buff)) || buff == OK)
	{
		check_arrow4(line, buff, history);
		if ((*line).mode_auto == 1)
		{
			quit_mode_auto(line);
			if (buff == OK && line->first_auto == 0)
				return (0);
			if (buff != OK && (ft_strlen((*line).tmp_str) != 0))
				display_str(line, buff);
		}
		if (have_to_break(line, buff, history) == -1)
			return (-1);
		im_in_last_col(line);
	}
	return (0);
}

void		winresize(int sig)
{
	struct winsize	sz;

	ioctl(0, TIOCGWINSZ, &sz);
	if (sig == SIGWINCH)
	{
		tputs(tgetstr("cl", NULL), 1, my_putchar);
		get_set_line(-1, NULL)->col = sz.ws_col;
		get_set_line(-1, NULL)->row = sz.ws_row;
		ft_putstr_fd(COLOR2, 1);
		ft_putstr_fd(get_set_line(-1, NULL)->prompt, 1);
		ft_putstr_fd(RESET2, 1);
		ft_putstr_fd(get_set_line(-1, NULL)->str, 1);
		get_set_line(-1, NULL)->curs = ft_strlen(get_set_line(-1, NULL)->str);
		get_set_line(-1, NULL)->my_in = 1;
		get_set_line(-1, NULL)->mode_select = 0;
		get_set_line(-1, NULL)->x = 0;
		if (get_set_line(-1, NULL)->mode_auto == 1)
		{
			free_mode_auto(get_set_line(-1, NULL));
			get_set_line(-1, NULL)->mode_auto = 0;
		}
		if (get_set_line(-1, NULL)->mode_ctrlr == 1)
			get_set_line(-1, NULL)->mode_ctrlr = 0;
	}
}
