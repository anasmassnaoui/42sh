/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   espace_n_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:47:13 by aariss            #+#    #+#             */
/*   Updated: 2020/01/12 12:58:38 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	escape_quote(char *line, char **str, int *i)
{
	(*i)++;
	if (line[*i] == '"')
	{
		*str = ft_joinchar(*str, 39);
		*str = ft_joinchar(*str, line[*i]);
		*str = ft_joinchar(*str, 39);
	}
	else if (line[*i] == 39)
	{
		*str = ft_joinchar(*str, '"');
		*str = ft_joinchar(*str, line[*i]);
		*str = ft_joinchar(*str, '"');
	}
	else
		*str = ft_joinchar(*str, line[*i]);
}

char	*escape_character(char *str, char *line, int *i, t_quote t)
{
	if (t.definer == 1)
	{
		(*i)++;
		if (line[*i] == '$')
			str = ft_joinchar(str, '$');
		else if (line[*i] == t.keeper && line[*i] == '"')
		{
			str = ft_joinchar(str, -7);
			str = ft_joinchar(str, t.keeper);
			str = ft_joinchar(str, -7);
		}
		else
		{
			str = ft_joinchar(str, 92);
			str = ft_joinchar(str, line[*i]);
		}
	}
	else if (t.definer == 0)
		escape_quote(line, &str, &(*i));
	return (str);
}
