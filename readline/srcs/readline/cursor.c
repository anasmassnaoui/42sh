/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:49:34 by hbenlarh          #+#    #+#             */
/*   Updated: 2019/11/08 13:25:02 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		get_current_row(void)
{
	char	buf[30];
	int		row;
	int		ch;
	int		i;

	row = 0;
	ch = 0;
	i = 0;
	write(1, "\033[6n", 4);
	while (ch != 'R')
	{
		read(0, &ch, 1);
		buf[i] = ch;
		i++;
	}
	if ((buf[3]) >= '0' && (buf[3] <= '9'))
		row = ((buf[2] - '0') * 10) + (buf[3] - '0');
	else
		row = buf[2] - '0';
	return (row);
}

void	go_to_pos(t_line *line)
{
	int count;

	count = 0;
	(*line).curs--;
	count = count_between_newlines(line);
	if (count > (*line).col)
		count = (count % (*line).col);
	if (verify_newline(line) != 0)
		tputs(tgoto(tgetstr("ch", NULL), 0, count - 1), 1, my_putchar);
	else
		tputs(tgoto(tgetstr("ch", NULL), 0, count
					+ (*line).msg_size), 1, my_putchar);
	(*line).curs++;
}

int		im_in_last_col(t_line *line)
{
	int a;
	int c;
	int d;

	a = possible_to_write(line);
	c = my_tmp_lenght(line);
	d = 0;
	if (c > a && (*line).curs != (int)ft_strlen((*line).str))
	{
		(*line).my_in--;
		a = possible_to_write(line);
		c = my_tmp_lenght(line);
		d = 1;
	}
	if (c > a && (*line).curs == (int)ft_strlen((*line).str))
		(*line).my_in--;
	if (d == 1)
		tputs(tgetstr("up", NULL), 1, my_putchar);
	return (0);
}

int		count_tmp_len(t_line *line)
{
	int i;
	int count;
	int tmp;

	i = 0;
	count = 0;
	tmp = 0;
	while (i < (int)ft_strlen((*line).str))
	{
		if ((*line).str[i] == '\n')
		{
			if (count < (*line).col)
				tmp += ((*line).col - count);
			count = 0;
		}
		else
			tmp++;
		count++;
		i++;
	}
	return (tmp);
}

int		count_lines(t_line *line)
{
	int i;
	int tmp;
	int count;

	i = -1;
	tmp = 0;
	count = 0;
	while (++i < (int)ft_strlen((*line).str))
	{
		if ((*line).str[i] == '\n')
		{
			tmp++;
			count = 0;
		}
		count++;
	}
	if (count + (*line).msg_size > (*line).col)
	{
		tmp += (count + (*line).msg_size) / (*line).col;
		if (((count + (*line).msg_size) % (*line).col) != 0)
			tmp++;
	}
	else
		tmp++;
	return (tmp);
}
