/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_col.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:33:06 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/04 13:27:32 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int	possible_to_write(t_line *line)
{
	int a;

	a = ((*line).row) - (*line).my_in;
	a++;
	return ((a * (*line).col));
}

int	get_count_line(t_line *line)
{
	int	c;
	int	count;
	int	i;

	i = 0;
	c = 0;
	count = (*line).msg_size;
	while (i < (int)ft_strlen((*line).str))
	{
		if ((*line).str[i] == '\n')
		{
			c++;
			count = -1;
		}
		if (count == (*line).col)
		{
			count = 0;
			c++;
		}
		i++;
		count++;
	}
	if (c >= 0)
		c++;
	return (c);
}

int	my_tmp_lenght(t_line *line)
{
	int c;

	c = get_count_line(line);
	return ((c * (*line).col));
}
