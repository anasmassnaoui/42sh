/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:04:29 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/02/15 13:15:11 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "auto.h"

int				my_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

void			prepare_termcap(struct termios	term)
{
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
}

void			signals_bis(t_line *line)
{
	if (get_set_holder(false, 0)->reset_readline == true)
	{
		if (line->mode_auto == 1)
		{
			free_mode_auto(line);
			line->mode_auto = 0;
		}
		ft_strdel(&line->str);
		line->str = ft_strdup("");
		ft_strdel(&line->cmd);
		line->cmd = ft_strdup("");
		line->mode_ctrlr = 0;
		line->curs = 0;
		get_set_holder(false, 0)->reset_readline = false;
	}
}

int				signals(t_line *line)
{
	if (get_set_holder(false, 0)->reset_readline == true &&
			ft_strcmp(line->prompt, "$> ") != 0)
	{
		ft_strdel(&line->cmd);
		line->cmd = ft_joinchar_glob(ft_strdup(""), -15);
		ft_strdel(&line->str);
		line->str = ft_strdup("");
		line->my_in = get_current_row();
		line->curs = 0;
		get_set_holder(false, 0)->reset_readline = false;
		return (-1);
	}
	signals_bis(line);
	return (0);
}

int				ctrl_d(t_line *line, int buff)
{
	if (buff == CTRLD)
		if (ctrl_d_handler(line) == -1)
			return (1);
	return (0);
}
