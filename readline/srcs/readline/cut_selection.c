/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_selection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:36:23 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/04 13:23:10 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	cut_selection2(t_line *line, int t)
{
	int start;
	int end;
	int c;
	int d;

	d = count_between_newlines(line) - t;
	c = count_between_newlines_after(line);
	start = (*line).curs - d;
	end = d + c;
	if (c + (*line).msg_size > (*line).col)
	{
		end = (*line).col;
		if (start == 0)
			end = end - (*line).msg_size;
	}
	go_home(line);
	(*line).str = cut_tmp(line, start, start + end);
	tputs(tgetstr("cd", NULL), 1, my_putchar);
	display_line(line);
	(*line).curs = ft_strlen((*line).str);
}

void	cut_selection3(t_line *line)
{
	int m;
	int c;
	int s;
	int start;
	int end;

	m = get_my_col_pos((*line).curs + (*line).msg_size, (*line).col);
	c = m * (*line).col;
	s = (*line).curs + (*line).msg_size - c;
	start = (*line).curs - s;
	end = (*line).col;
	if (m == 0)
		start = 0;
	if (start + (*line).col > (int)ft_strlen((*line).str))
		end = ft_strlen((*line).str) - start;
	go_home(line);
	(*line).str = cut_tmp(line, start, start + end);
	tputs(tgetstr("cd", NULL), 1, my_putchar);
	display_line(line);
	(*line).curs = ft_strlen((*line).str);
}

void	cut_selection(t_line *line)
{
	int t;
	int d;

	if ((*line).mode_select == 1)
		cut_selection1(line);
	else
	{
		if (verify_newline(line) == 0)
			t = 0;
		else
			t = 1;
		d = count_between_newlines(line) - t;
		if (d + (*line).msg_size > (*line).col)
			cut_selection3(line);
		else
			cut_selection2(line, t);
	}
}

char	*cut_tmp(t_line *line, int x, int y)
{
	int		len;
	char	*tmp;
	int		i;

	len = ft_strlen((*line).str) - (y - x) + 1;
	tmp = malloc(sizeof(char) * len);
	i = 0;
	while (i < x)
	{
		tmp[i] = (*line).str[i];
		i++;
	}
	while (y < (int)ft_strlen((*line).str))
	{
		tmp[i] = (*line).str[y];
		y++;
		i++;
	}
	tmp[i] = '\0';
	free((*line).str);
	return (tmp);
}
