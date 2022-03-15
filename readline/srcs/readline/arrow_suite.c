/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_suite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:09:17 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/02/06 21:46:32 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "auto.h"

void	go_home(t_line *line)
{
	tputs(tgetstr("vi", NULL), 1, my_putchar);
	while ((*line).curs > 0)
		go_left(line);
	tputs(tgetstr("ve", NULL), 1, my_putchar);
}

void	go_end(t_line *line)
{
	tputs(tgetstr("vi", NULL), 1, my_putchar);
	while ((*line).curs < (int)ft_strlen((*line).str))
		go_right(line);
	tputs(tgetstr("ve", NULL), 1, my_putchar);
}

void	clear_window(t_line *line)
{
	go_home(line);
	tputs(tgetstr("cl", NULL), 1, my_putchar);
	print_prompt("$> ");
	ft_putstr_fd(line->str, 1);
	line->curs = ft_strlen(line->str);
	line->my_in = 1;
	if (line->mode_auto == 1)
	{
		free_mode_auto(line);
		line->mode_auto = 0;
	}
	if (line->mode_ctrlr == 1)
		line->mode_ctrlr = 0;
}
