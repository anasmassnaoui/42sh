/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displaytmpstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:26:43 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/05 12:20:00 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"

int		count_lines_str(t_line *line)
{
	int i;
	int tmp;
	int count;

	i = -1;
	tmp = 0;
	count = 0;
	while (++i < (int)ft_strlen((*line).tmp_str))
	{
		if ((*line).tmp_str[i] == '\n')
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

void	pos_curs_correctly2(t_line *line)
{
	int a;
	int b;

	b = (*line).curs + (*line).msg_size;
	a = (*line).my_in - 1;
	if (b > (*line).col)
	{
		a = b / (*line).col;
		a = (*line).my_in + a - 1;
		b = b % (*line).col;
	}
	tputs(tgetstr("vi", 0), 0, my_putchar);
	tputs(tgoto(tgetstr("cm", NULL), b, a), 1, my_putchar);
	tputs(tgetstr("ve", 0), 0, my_putchar);
}

char	*join_two_chars(char *str, char *tmp, int n)
{
	char	*newchar;
	int		i;
	int		j;

	i = -1;
	j = 0;
	newchar = malloc(sizeof(char) * ((ft_strlen(str) + ft_strlen(tmp)) + 1));
	while (str[++i] != '\0' && i < n)
		newchar[i] = str[i];
	while (j < (int)ft_strlen(tmp))
	{
		newchar[i] = tmp[j];
		j++;
		i++;
	}
	while (n < (int)ft_strlen(str))
	{
		newchar[i] = str[n];
		n++;
		i++;
	}
	newchar[i] = '\0';
	return (newchar);
}
