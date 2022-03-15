/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_syntax_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:27:03 by aariss            #+#    #+#             */
/*   Updated: 2020/02/12 13:32:50 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	skippy(char **line)
{
	MAD_DECLARE(int, keeper, **line);
	*line += 1;
	while (**line && **line != keeper)
	{
		if (**line == 92 && *(*line + 1) == keeper)
			*line += 1;
		*line += 1;
	}
}

int		avoid_quote(char *line, int i, int param)
{
	int keeper;

	keeper = line[i];
	i++;
	while (line[i] != keeper && line[i])
		i++;
	if (line[i] && line[i] == keeper)
		if (param)
			i++;
	return (i);
}

int		count_and(char **line, int *how_many)
{
	*how_many = 0;
	while (**line && **line == '&')
	{
		*how_many += 1;
		*line += 1;
	}
	if (**line == ' ')
	{
		while (**line && **line == ' ')
			*line += 1;
		if (**line == '&' || **line == '|' || **line == ';')
			return (0);
	}
	if (*how_many > 2 || **line == '|')
		return (0);
	return (1);
}

int		count_or(char **line, int *how_many)
{
	*how_many = 0;
	while (**line && **line == '|')
	{
		*how_many += 1;
		*line += 1;
	}
	if (**line == ' ')
	{
		while (**line && **line == ' ')
			*line += 1;
		if (**line == '&' || **line == '|' || **line == ';')
			return (0);
	}
	if (*how_many > 2 || ft_istoken(**line))
		return (0);
	if (**line == '\0')
		return (0);
	return (1);
}

int		coma_trickster(char **line)
{
	if (!(*(*line - 1)))
		return (0);
	*line += 1;
	while (**line && **line == ' ')
		*line += 1;
	if (!ft_isalnum(**line))
		return (0);
	return (1);
}
