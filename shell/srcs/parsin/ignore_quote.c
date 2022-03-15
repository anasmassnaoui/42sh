/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:43:22 by aariss            #+#    #+#             */
/*   Updated: 2020/02/14 16:43:25 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*fill_till(char *str, char **line, int till)
{
	str = ft_joinchar(str, **line);
	*line += 1;
	while (**line && **line != till)
	{
		str = ft_joinchar(str, **line);
		*line += 1;
	}
	str = ft_joinchar(str, **line);
	return (str);
}

char	*quote_found(char *str, char **line, int pick)
{
	(!pick) ? str = ft_joinchar(str, **line) : 0;
	MAD_DECLARE(int, keeper, **line);
	*line += 1;
	while (**line && **line != keeper)
	{
		if (pick && **line == -7)
		{
			*line += 2;
			str = ft_joinchar(str, keeper);
		}
		else if (!pick && **line == -7)
		{
			str = ft_joinchar(str, -7);
			str = ft_joinchar(str, keeper);
			str = ft_joinchar(str, -7);
			*line += 2;
		}
		else
			str = ft_joinchar(str, **line);
		*line += 1;
	}
	(!pick) ? str = ft_joinchar(str, **line) : 0;
	return (str);
}

char	*ignore_quote(char *line, int pick)
{
	char	*str;

	str = ft_strdup("");
	while (*line)
	{
		if (ft_iswhite(*line))
			str = ft_joinchar(str, -1);
		else if (ft_isquote(*line))
			str = quote_found(str, &line, pick);
		else if (*line == HEREDOC)
			str = fill_till(str, &line, HEREDOC);
		else if (*line == '$' && *(line + 1) == '{')
		{
			str = ft_joinchar(str, *line);
			line += 1;
			str = fill_till(str, &line, '}');
		}
		else
			str = ft_joinchar(str, *line);
		line += 1;
	}
	return (str);
}
