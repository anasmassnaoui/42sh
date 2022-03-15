/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_and_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 14:31:32 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/06 13:13:55 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"

void	display_sugg_move(t_line *line)
{
	int		t;
	int		max;
	t_names	*tmp;
	int		col;

	tmp = (*line).names;
	max = maxlen(tmp) + 1;
	col = (*line).col / max;
	if (((*line).col % max) != 0)
		col--;
	if (col == 0)
		col++;
	t = (count_sugg(tmp) / col);
	if ((count_sugg(tmp) % col) != 0)
		t++;
	if ((*line).mode != 2)
		move_in_modes(line, max, col, t);
	if ((*line).mode == 2)
	{
		free_head_to_scroll(line);
		move_in_modes(line, max, col, (*line).row - 1);
	}
	pos_curs_correctly2(line);
}

void	move_in_modes(t_line *line, int max, int col, int t)
{
	t_names			*tmp;
	t_autocmp_draw	draw;

	tmp = (*line).names;
	draw = init_draw_glob(line);
	while (draw.d < col)
	{
		draw.l = 0;
		while (draw.l < t && tmp)
		{
			tputs(tgoto(tgetstr("cm", NULL), draw.j, draw.i), 1, my_putchar);
			tmp->col = draw.j;
			tmp->row = draw.i;
			if (tmp->active == 1)
				tputs(tgetstr("mr", 0), 0, my_putchar);
			draw.len = display_name(tmp->name);
			tputs(tgetstr("me", 0), 0, my_putchar);
			tmp = tmp->next;
			draw.l++;
			draw.i = draw.i + calc_height_of_name(draw.len, (*line).col);
		}
		draw.j += max + 1;
		draw.i = (*line).my_in + count_lines_str(line) - 1;
		draw.d++;
	}
}

void	move_in_modes_normal(t_line *line, int max, int col, int t)
{
	t_names			*tmp;
	t_autocmp_draw	draw;

	tmp = (*line).names;
	draw = init_draw_glob(line);
	while (draw.d < col)
	{
		draw.l = 0;
		while (draw.l < t && tmp)
		{
			tputs(tgoto(tgetstr("cm", NULL), draw.j, draw.i), 1, my_putchar);
			tmp->col = draw.j;
			tmp->row = draw.i;
			if (tmp->active == 1)
				tputs(tgetstr("mr", 0), 0, my_putchar);
			draw.len = display_name(tmp->name);
			tputs(tgetstr("me", 0), 0, my_putchar);
			tmp = tmp->next;
			draw.l++;
			draw.i = draw.i + calc_height_of_name(draw.len, (*line).col);
		}
		draw.j += max + 1;
		draw.i = (*line).my_in + count_lines(line) - 1;
		draw.d++;
	}
}
