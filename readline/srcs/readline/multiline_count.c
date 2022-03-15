/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiline_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:53:13 by hbenlarh          #+#    #+#             */
/*   Updated: 2019/11/08 14:01:13 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

int		count_between_newlines(t_line *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < (*line).curs)
	{
		if ((*line).str[i] == '\n')
		{
			count = 0;
		}
		i++;
		count++;
	}
	return (count);
}

int		count_between_newlines_after(t_line *line)
{
	int i;
	int count;

	i = (*line).curs;
	count = 0;
	while ((*line).str[i] != '\n' && (*line).str[i] != '\0')
	{
		i++;
		count++;
	}
	return (count);
}

int		count_last_newlines(t_line *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < (int)ft_strlen((*line).str))
	{
		if ((*line).str[i] == '\n')
			count = 0;
		i++;
		count++;
	}
	return (count);
}

int		verify_newline(t_line *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < (*line).curs)
	{
		if ((*line).str[i] == '\n')
			count++;
		i++;
	}
	return (count);
}
