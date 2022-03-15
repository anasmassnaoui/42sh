/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:25:31 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/04 13:26:35 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int			get_my_col_pos(int curs, int col)
{
	int d;

	d = curs / col;
	return (d);
}

int			verify_if_exit_multiline(t_line *line)
{
	int count;
	int i;
	int d;

	count = 0;
	i = (*line).curs;
	d = (*line).curs;
	while (i < (d + (*line).col) && (*line).str[i] != '\0')
	{
		if ((*line).str[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

int			count_between_newlines_after2(t_line *line)
{
	int i;
	int count;

	i = (*line).curs + 1;
	count = 0;
	while ((*line).str[i] != '\n' && (*line).str[i] != '\0')
	{
		i++;
		count++;
	}
	return (count);
}
