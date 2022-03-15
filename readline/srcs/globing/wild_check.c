/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:38:20 by aariss            #+#    #+#             */
/*   Updated: 2020/01/28 16:38:23 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"

t_map		init_map(void)
{
	t_map edge;

	edge.directory = NULL;
	edge.hint = NULL;
	edge.wild = NULL;
	return (edge);
}

int			ft_isquote_glob(int c)
{
	if (c == 39 || c == '"')
		return (1);
	return (0);
}

int			is_wild(char character)
{
	if (character == '?' || character == '*' || character == ']')
		return (1);
	return (0);
}

int			is_valid_bracket(const char *wild, int cursor)
{
	while (wild[cursor] && cursor > 0)
	{
		if (wild[cursor] == ']')
		{
			if (!opened_bracket(wild, &cursor))
				return (0);
		}
		else if (wild[cursor] == '[')
			return (0);
		cursor -= 1;
	}
	return (1);
}

int			is_bracket_wild(const char *line, size_t cursor)
{
	int	count;

	count = 0;
	while (cursor > 0 && line[cursor] != '[')
	{
		if (line[cursor] == '-')
			if (line[cursor - 1] != '[' && line[cursor + 1] != ']')
				count += 1;
		cursor -= 1;
	}
	if (line[cursor] == '[' && count == 1)
		return (1);
	return (0);
}
