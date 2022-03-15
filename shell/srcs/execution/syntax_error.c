/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:10:26 by aariss            #+#    #+#             */
/*   Updated: 2019/08/16 20:26:27 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		token_scout(char *line)
{
	if (ft_strlen(line) == 0)
		return (1);
	else
	{
		while (*line && *line == ' ')
			line += 1;
		if (*line == '\0' || *line == ';')
			return (1);
	}
	return (0);
}

int		token_mapper(char *line)
{
	int	i;

	i = 1;
	if (line[0] == '>')
	{
		while (line[i] && line[i] == '>')
			i += 1;
	}
	else if (line[0] == '<')
	{
		while (line[i] && line[i] == '<')
			i += 1;
	}
	if (i > 2)
		return (0);
	return (1);
}

int		pipe_scout(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i += 1;
	if (line[i] == '|')
		return (0);
	return (1);
}

int		syntax_checker(char *line)
{
	MAD_DECLARE(int, how_many, 0);
	MAD_DECLARE(char *, pline, no_more_space(&line));
	while (*line)
	{
		if (*line == '&')
			if (*pline == *line || !count_and(&line, &how_many))
				return (0);
		if (*line == '|')
			if (*pline == *line || !count_or(&line, &how_many))
				return (0);
		if (*line == ';')
			if (*pline == *line || !coma_trickster(&line))
				return (0);
		if (*line == '$' && *(line + 1) == '$' && *(line + 2) == '(')
			return (0);
		if ((*line == '>' || *line == '<') && !weird_tokens(&line))
			return (0);
		if (ft_isquote(*line))
			skippy(&line);
		if (*line == '\0')
			break ;
		line += 1;
	}
	return (1);
}

void	reset_fds(void)
{
	int fd;

	fd = open("/dev/tty", O_RDWR);
	dup2(fd, 1);
	dup2(fd, 2);
	if (fd > 2)
		close(fd);
}
