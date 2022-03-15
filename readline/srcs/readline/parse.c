/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:03:35 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/28 16:05:40 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "auto.h"

int	get_escape(t_line *line)
{
	int i;

	i = ft_strlen((*line).str);
	if (i - 2 >= 0 && (*line).str[i - 2] == 92)
		return (-1);
	return (0);
}

int	get_cote_count(t_line *line)
{
	size_t i;
	size_t j;

	i = -1;
	j = 0;
	while (++i < ft_strlen((*line).cmd))
	{
		while ((*line).cmd[i] == ' ' || (*line).cmd[i] == '\t')
			i++;
		if (((*line).cmd[i] == 34) && ((*line).cmd[i - 1] != 92))
		{
			j = i;
			if (get_count_two(&j, (*line).cmd, 34) == -1)
				return (-1);
			i = j + 1;
		}
		else if (((*line).cmd[i] == 39) && ((*line).cmd[i - 1] != 92))
		{
			j = i;
			if (get_count_two(&j, (*line).cmd, 39) == -1)
				return (-1);
			i = j + 1;
		}
	}
	return (0);
}

int	get_count_two(size_t *j, char *line, char c)
{
	while ((line[(*j)] != '\0' && line[(*j) + 1] != c) ||
			((line[(*j)] == 92) && c != 39))
		*j = *j + 1;
	if (*j == ft_strlen(line))
		return (-1);
	else
		return (0);
}
