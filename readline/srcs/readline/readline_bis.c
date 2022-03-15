/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:15:13 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/29 12:33:25 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "auto.h"

t_line	*initial_line_two(char *prompt, t_line *line)
{
	(*line).msg_size = ft_strlen(prompt);
	(*line).tmp_curs = 1;
	(*line).hint = NULL;
	(*line).ground = NULL;
	(*line).tmp_str = ft_strdup("");
	(*line).mode_search = 0;
	(*line).last_curs_pos = -1;
	(*line).mode_ctrlr = 0;
	(*line).first_time = 0;
	(*line).prompt = ft_strdup(prompt);
	(*line).result = ft_strdup("");
	(*line).first_auto = 0;
	(*line).mode_auto = 0;
	return (line);
}

t_line	initial_line(char *prompt)
{
	struct winsize	sz;
	t_line			line;

	ioctl(0, TIOCGWINSZ, &sz);
	line.col = sz.ws_col;
	line.row = sz.ws_row;
	line.in = get_current_row();
	line.my_in = get_current_row();
	line.curs = 0;
	line.str = ft_strdup("");
	line.copy = ft_strdup("");
	line.cmd = ft_strdup("");
	line.x = -1;
	line.index_history = -1;
	line.mode_select = 0;
	line.mode_auto = 0;
	initial_line_two(prompt, &line);
	return (line);
}

void	go_to_end_line(t_line *line, int buff)
{
	if (buff == OK)
	{
		line->mode_select = 0;
		if (((*line).curs != (int)ft_strlen((*line).str)))
			go_end(line);
	}
}

void	check_arrow3(t_line *line, int buff, t_all_hist *history)
{
	if (buff == RIGHT && (*line).mode_auto == 0)
		go_right(line);
	else if (buff == LEFT && (*line).mode_auto == 0)
		go_left(line);
	else if (buff == CTRLL)
		clear_window(line);
	else if (buff == UP)
		display_history_up(history, line);
	else if (buff == DOWN)
		display_history_down(history, line);
	else if (buff == HOME)
		go_home(line);
	else if (buff == END)
		go_end(line);
	else if (buff == TAB && (*line).mode_auto == 0)
	{
		get_ground_hint(line);
		check_tab_and_mode(line);
	}
	else if (buff == TAB && (*line).mode_auto == 1)
		move_tab(line, (*line).names);
}

t_line	*get_set_line(int i, t_line *l)
{
	static t_line	*line;

	if (i == 0)
		line = l;
	return (line);
}
