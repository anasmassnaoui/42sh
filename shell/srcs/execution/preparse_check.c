/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 11:02:29 by aariss            #+#    #+#             */
/*   Updated: 2020/01/26 11:02:32 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		just_spaces(char *line)
{
	while (*line)
	{
		if (ft_isspace(*line))
			line++;
		else
			return (0);
	}
	return (1);
}

t_bool	is_empty(char *line)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (line[i])
	{
		if (!ft_iswhite(line[i]))
			return (false);
		i += 1;
	}
	return (true);
}

char	*no_more_space(char **line)
{
	*line = kill_one(*line, '\n');
	while (**line && **line == ' ')
		*line += 1;
	MAD_DECLARE(char *, pline, *line);
	return (pline);
}
