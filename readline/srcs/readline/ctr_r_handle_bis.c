/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctr_r_handle_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:25:31 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/28 16:35:29 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "auto.h"

int		count_lines_r(t_line *line)
{
	int	i;
	int	tmp;
	int count;

	i = -1;
	tmp = 0;
	count = 0;
	while (++i < (int)ft_strlen((*line).result))
	{
		if ((*line).result[i] == '\n')
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

void	pos_curs_correctly_r(t_line *line)
{
	int a;
	int b;

	a = count_lines_r(line);
	b = (*line).curs + (*line).msg_size;
	if (b > (*line).col)
		b = b % (*line).col;
	tputs(tgoto(tgetstr("cm", NULL), b, (*line).my_in + a - 2), 1, my_putchar);
}

void	display_ctrr_search(t_line *line, char *tmp_line)
{
	pos_curs_correctly_r(line);
	ft_putstr_fd("\nbck-i-search : ", 1);
	ft_putstr_fd(tmp_line, 1);
}
