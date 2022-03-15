/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctr_r_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 13:19:57 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/02/15 17:34:57 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "auto.h"

void	select_a_letter(char *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c && j == 0)
		{
			tputs(tgetstr("mr", NULL), 1, my_putchar);
			j = 1;
		}
		ft_putchar_fd(str[i], 1);
		tputs(tgetstr("me", NULL), 1, my_putchar);
		i++;
	}
}

void	prepare_cntr_r(t_line *line)
{
	if (line->mode_ctrlr == 0)
	{
		if (line->row == line->my_in)
		{
			tputs(tgetstr("cl", NULL), 1, my_putchar);
			line->my_in = 1;
			line->curs = 0;
			print_prompt(line->prompt);
		}
		pos_curs_correctly(line);
		ft_strdel(&line->str);
		line->str = ft_strdup("");
		line->curs = 0;
		ft_putstr_fd("\nbck-i-search : ", 1);
		line->mode_ctrlr = 1;
	}
}

void	quit_ctrlr_mode(t_line *line, char *result)
{
	tputs(tgoto(tgetstr("cm", NULL), 3, (*line).my_in - 1), 1, my_putchar);
	tputs(tgetstr("cd", NULL), 1, my_putchar);
	if (ft_strlen(result))
	{
		ft_strdel(&line->str);
		line->str = ft_strdup(result);
	}
	ft_putstr(line->str);
	line->curs = ft_strlen(line->str);
	line->mode_ctrlr = 0;
}

void	display_ctrl_result(t_line *line, char *result)
{
	char *tmp_line;

	if (result != NULL)
	{
		tputs(tgoto(tgetstr("cm", NULL), 3, (*line).my_in - 1), 1, my_putchar);
		tputs(tgetstr("cd", NULL), 1, my_putchar);
		tmp_line = line->str;
		select_a_letter(result, line->str[0]);
		display_ctrr_search(line, tmp_line);
	}
}
