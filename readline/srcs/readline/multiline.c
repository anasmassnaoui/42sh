/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:01:24 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/02/14 11:02:56 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		count_multiline(t_line *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < (int)ft_strlen((*line).str))
	{
		if ((*line).str[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

void	add_line_messaage(void)
{
	ft_putstr(COLOR2);
	ft_putstr(".. ");
	ft_putstr(RESET2);
}

int		verify_if_exist_multiline(t_line *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while ((*line).str[i])
	{
		if ((*line).str[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

int		verify_newline_left(t_line *line)
{
	int j;
	int count;

	j = 0;
	count = 0;
	while (j < (*line).curs)
	{
		count++;
		if ((*line).str[j] == '\n')
			count = 0;
		j++;
	}
	if ((count % (*line).col) == 0)
	{
		return (1);
	}
	return (0);
}

void	go_left_2(t_line *line)
{
	if ((*line).str[(*line).curs - 1] == '\n')
	{
		go_up((*line).col);
		go_to_pos(line);
	}
	else if (verify_newline_left(line) == 1)
	{
		go_up((*line).col);
	}
	else
		tputs(tgetstr("le", NULL), 1, my_putchar);
}
