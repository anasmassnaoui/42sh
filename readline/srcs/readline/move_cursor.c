/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:58:15 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/04 13:28:28 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	go_up_line3(t_line *line, int old_d)
{
	int i;
	int d;

	i = -1;
	d = count_between_newlines(line);
	if (d >= (*line).col)
	{
		d = d % (*line).col;
		while (++i < (d - old_d))
			go_left(line);
	}
	else
	{
		if (verify_newline(line) == 0)
			d++;
		while (++i < (d - old_d))
			go_left(line);
	}
}

void	go_up_line2(t_line *line, int old_d)
{
	if ((*line).str[(*line).curs] == '\n')
		go_left(line);
	if (old_d >= (*line).col)
	{
		tputs(tgetstr("up", NULL), 1, my_putchar);
		(*line).curs = (*line).curs - (*line).col;
	}
	else
	{
		while ((*line).str[(*line).curs] != '\n')
			go_left(line);
		go_up_line3(line, old_d);
	}
}

void	go_up_line(t_line *line)
{
	int d;
	int old_d;

	old_d = count_between_newlines(line);
	if (verify_newline(line) != 0)
		go_up_line2(line, old_d);
	else
	{
		if ((*line).curs - (*line).col + 1 > 0)
		{
			d = ((*line).curs + (*line).msg_size) / (*line).col;
			if (d > 0)
				tputs(tgetstr("up", NULL), 1, my_putchar);
			(*line).curs = (*line).curs - (*line).col;
		}
	}
}

void	go_down_line2(t_line *line, int d)
{
	int new_d;
	int i;

	i = 0;
	new_d = count_between_newlines_after2(line);
	(d == 0) ? go_right(line) : 1;
	if (d > (*line).col)
		d = d % (*line).col;
	if (d < new_d)
	{
		while (i < d)
		{
			go_right(line);
			i++;
		}
	}
	else
	{
		(new_d < d) ? new_d++ : 1;
		while (i < new_d)
		{
			go_right(line);
			i++;
		}
	}
}

void	go_down_line(t_line *line)
{
	int d;
	int i;
	int c;

	d = count_between_newlines(line);
	i = 0;
	c = (*line).curs;
	if (verify_if_exit_multiline(line) == 0)
	{
		while (i < (*line).col && (c + (*line).col) <=
				(int)ft_strlen((*line).str))
		{
			go_right(line);
			i++;
		}
	}
	else
	{
		if (verify_newline(line) == 0)
			d++;
		while ((*line).str[(*line).curs] != '\n' &&
				(*line).curs < (int)ft_strlen((*line).str))
			go_right(line);
		go_down_line2(line, d);
	}
}
