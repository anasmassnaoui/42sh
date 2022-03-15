/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:07:55 by hbenlarh          #+#    #+#             */
/*   Updated: 2019/11/07 16:43:51 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	copy_mode_select(t_line *line, int i)
{
	(*line).mode_select = 0;
	tputs(tgetstr("sc", NULL), 1, my_putchar);
	go_home(line);
	tputs(tgetstr("cd", NULL), 1, my_putchar);
	display_line(line);
	tputs(tgetstr("rc", NULL), 1, my_putchar);
	(*line).curs = i;
	if ((*line).copy)
		free((*line).copy);
	if ((*line).x < (*line).curs)
		(*line).copy = ft_strsub((*line).str,
				(*line).x, (*line).curs - (*line).x);
	else if ((*line).x > (*line).curs)
		(*line).copy = ft_strsub((*line).str, (*line).curs + 1,
				(*line).x - (*line).curs);
}

t_copy	get_start_end(t_line *line)
{
	t_copy	copy;

	copy.start = 0;
	copy.end = 0;
	if (verify_newline(line) == 0)
		copy.t = 0;
	else
		copy.t = 1;
	copy.d = count_between_newlines(line) - copy.t;
	copy.c = count_between_newlines_after(line);
	return (copy);
}

void	getcopy_select1(t_line *line, t_copy copy)
{
	int		i;

	i = (*line).curs;
	copy.d = get_my_col_pos(i + (*line).msg_size, (*line).col);
	copy.c = copy.d * (*line).col;
	copy.s = i + (*line).msg_size - copy.c;
	copy.start = (*line).curs - copy.s;
	copy.end = (*line).col;
	if (copy.d == 0)
		copy.start = 0;
	if (copy.start + (*line).col > (int)ft_strlen((*line).str))
		copy.end = ft_strlen((*line).str) - copy.start;
	(*line).copy = ft_strsub((*line).str, copy.start, copy.end);
}

void	getcopy_select(t_line *line)
{
	t_copy	copy;

	copy = get_start_end(line);
	if (copy.d + (*line).msg_size > (*line).col)
	{
		getcopy_select1(line, copy);
	}
	else
	{
		copy.start = (*line).curs - copy.d;
		copy.end = copy.d + copy.c;
		if (copy.c + (*line).msg_size > (*line).col)
		{
			copy.end = (*line).col;
			if (copy.start == 0)
				copy.end = copy.end - (*line).msg_size;
		}
		(*line).copy = ft_strsub((*line).str, copy.start, copy.end);
	}
}

void	get_line_copy(t_line *line)
{
	int i;

	i = (*line).curs;
	if ((*line).mode_select == 0)
	{
		getcopy_select(line);
	}
	else
		copy_mode_select(line, i);
}
