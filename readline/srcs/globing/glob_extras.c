/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_extras.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:58:22 by aariss            #+#    #+#             */
/*   Updated: 2020/01/28 16:38:15 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"

int		special_count(const char *hint)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (hint[i] && hint[i] != ']')
	{
		if (hint[i] == '-')
			count += 1;
		i += 1;
	}
	return (count + i + 1);
}

int		seer(const char *hint)
{
	int count;

	count = 0;
	while (*hint)
	{
		if (*hint == '[')
		{
			while (*hint && *hint != ']')
				hint += 1;
			count += 1;
		}
		else
			count += 1;
		hint += 1;
	}
	return (count);
}

void	characters_match(char **string, char **hint)
{
	while ((**string == **hint) && **string && **hint)
	{
		*string += 1;
		*hint += 1;
	}
}

int		is_wild_token(char c)
{
	if (c == '*' || c == '?' || c == '[')
		return (1);
	return (0);
}

int		wild_quote_skipper(const char *line, size_t cursor)
{
	int keeper;

	keeper = line[cursor--];
	while (cursor > 0 && line[cursor] && line[cursor] != keeper)
		cursor -= 1;
	return (cursor);
}
