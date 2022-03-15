/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_autocmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 12:53:30 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/28 14:25:57 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"

void	free_2d(char **tmp)
{
	int i;

	i = 0;
	while (tmp[i])
	{
		ft_strdel(&tmp[i]);
		i++;
	}
	free(tmp);
}

int		calc_height_of_name(int len, int col)
{
	int count;

	count = 0;
	if (len > col)
	{
		count = len / col;
		if (len % col != 0)
			count++;
		return (count);
	}
	return (1);
}

void	free_head_to_scroll(t_line *line)
{
	t_names *tmp1;
	t_names *todel;

	tmp1 = (*line).names;
	while (tmp1)
	{
		if (tmp1->active == 1)
		{
			if (tmp1->row == (*line).row - 1)
			{
				todel = (*line).names;
				(*line).names = (*line).names->next;
				ft_strdel(&todel->name);
				free(todel);
			}
		}
		tmp1 = tmp1->next;
	}
}
