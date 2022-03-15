/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_selection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:06:32 by hbenlarh          #+#    #+#             */
/*   Updated: 2019/11/07 15:07:37 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	get_x_y(t_line *line)
{
	(*line).mode_select = 1;
	(*line).x = (*line).curs;
}

void	delete_and_display_right(t_line *line)
{
	int i;

	tputs(tgetstr("sc", NULL), 1, my_putchar);
	tputs(tgetstr("cd", NULL), 1, my_putchar);
	i = (*line).curs;
	ft_putstr(COLOR1);
	ft_putchar((*line).str[i]);
	ft_putstr(RESET);
	i++;
	while (i < (int)ft_strlen((*line).str) && (*line).str[i] != '\0')
	{
		ft_putchar((*line).str[i]);
		i++;
	}
	tputs(tgetstr("rc", NULL), 1, my_putchar);
}

void	delete_and_display_left(t_line *line, int x, int y)
{
	tputs(tgetstr("sc", NULL), 1, my_putchar);
	tputs(tgetstr("cd", NULL), 1, my_putchar);
	ft_putstr(COLOR1);
	while (x < y)
	{
		ft_putchar((*line).str[x]);
		x++;
	}
	ft_putstr(RESET);
	while ((*line).str[x] != '\0')
	{
		ft_putchar((*line).str[x]);
		x++;
	}
	tputs(tgetstr("rc", NULL), 1, my_putchar);
}
