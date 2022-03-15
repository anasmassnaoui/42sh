/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seperatos_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:14:17 by aariss            #+#    #+#             */
/*   Updated: 2020/01/12 18:14:19 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		seperators_check(char c, char d)
{
	if ((c == '&' && d == '&')
		|| (c == '|' && d == '|')
		|| (c == '&' && !ft_istoken(d)))
		return (1);
	return (0);
}

void	seperators_parse(char *line, char **str, int *i)
{
	if (!ft_istoken(line[(*i) - 1])
		&& line[*i] == '&' && !ft_istoken(line[(*i) + 1]))
	{
		*str = ft_joinchar(*str, SEPERATOR);
		*str = ft_joinchar(*str, BACKGROUND_AND);
		*str = ft_joinchar(*str, SEPERATOR);
	}
	else if (line[*i] == '&' && line[(*i) + 1] == '&')
	{
		*str = ft_joinchar(*str, SEPERATOR);
		*str = ft_joinchar(*str, AND);
		*str = ft_joinchar(*str, SEPERATOR);
		(*i) += 1;
	}
	else if (line[*i] == '|' && line[(*i) + 1] == '|')
	{
		*str = ft_joinchar(*str, SEPERATOR);
		*str = ft_joinchar(*str, OR);
		*str = ft_joinchar(*str, SEPERATOR);
		(*i) += 1;
	}
}
