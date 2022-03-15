/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:44:31 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/02/14 11:01:10 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	go_right_2(t_line *line)
{
	if (verify_newline(line) == 0)
		go_down();
	else
		tputs(tgetstr("nd", NULL), 1, my_putchar);
}

void	go_right(t_line *line)
{
	int count;

	count = count_between_newlines(line);
	if ((*line).mode_select == 1)
		delete_and_display_right(line);
	if ((*line).curs < (int)ft_strlen((*line).str))
	{
		if (verify_newline(line) != 0)
			if ((count) % (*line).col == 0)
			{
				go_down();
				(*line).curs++;
				return ;
			}
		if ((*line).str[(*line).curs] == '\n')
			go_down();
		else if (((*line).curs + (*line).msg_size + 1) % (*line).col == 0)
			go_right_2(line);
		else
			tputs(tgetstr("nd", NULL), 1, my_putchar);
		(*line).curs++;
	}
}

void	go_left(t_line *line)
{
	if ((*line).curs > 0)
	{
		if ((*line).mode_select == 1)
			delete_and_display_left(line,
					(*line).curs, (*line).x + 1);
		if (verify_newline(line) == 0)
		{
			if (((((*line).curs + (*line).msg_size) % (*line).col) == 0))
				go_up((*line).col);
			else
				tputs(tgetstr("le", NULL), 1, my_putchar);
		}
		else
		{
			go_left_2(line);
		}
		(*line).curs--;
	}
}

void	go_up(int col)
{
	tputs(tgetstr("up", NULL), 1, my_putchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, col - 1), 1, my_putchar);
}

void	go_down(void)
{
	tputs(tgetstr("do", NULL), 1, my_putchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, my_putchar);
}
