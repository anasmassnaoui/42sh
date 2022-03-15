/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weird_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:25:00 by aariss            #+#    #+#             */
/*   Updated: 2020/02/12 13:25:02 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		jumper(char **line)
{
	if (*(*line + 1) == ' ')
	{
		*line += 1;
		while (**line && **line == ' ')
			*line += 1;
		return (1);
	}
	return (0);
}

int		weird_handler(char **line, int first, int second)
{
	int	x;

	x = 0;
	if (**line == first)
	{
		x = jumper(line);
		if ((x && **line == second) || (!x && *(*line + 1) == second))
			return (0);
	}
	return (1);
}

int		weird_tokens(char **line)
{
	if (!pipe_scout(*line + 1)
			|| token_scout(*line + 1) || !token_mapper(*line))
		return (0);
	else if (!weird_handler(line, '>', '<') || !weird_handler(line, '<', '>'))
		return (0);
	return (1);
}
