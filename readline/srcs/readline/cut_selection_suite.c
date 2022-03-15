/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_selection_suite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:43:20 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/04 13:22:33 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	cut_part(t_line *line, int x, int y)
{
	int t;

	t = 0;
	go_home(line);
	if ((*line).str[y] == '\n')
		t = 1;
	(*line).str = cut_tmp(line, x, y + t);
	tputs(tgetstr("cd", NULL), 1, my_putchar);
	display_line(line);
	(*line).curs = ft_strlen((*line).str);
	(*line).mode_select = 0;
}

void	cut_selection1(t_line *line)
{
	if ((*line).copy)
		free((*line).copy);
	if ((*line).x < (*line).curs)
		(*line).copy = ft_strsub((*line).str, (*line).x,
				(*line).curs - (*line).x);
	else if ((*line).x > (*line).curs)
		(*line).copy = ft_strsub((*line).str, (*line).curs + 1,
				(*line).x - (*line).curs);
	if ((*line).x < (*line).curs)
		cut_part(line, (*line).x, (*line).curs);
	else if ((*line).x > (*line).curs)
		cut_part(line, (*line).curs, (*line).x + 1);
}
