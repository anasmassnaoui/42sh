/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 11:52:21 by aariss            #+#    #+#             */
/*   Updated: 2020/01/12 16:50:16 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsin.h"

char	*quote_treatement(char *line, char *str, int *i, t_quote spec)
{
	spec.keeper = line[*i];
	str = ft_joinchar(str, line[*i]);
	(*i)++;
	while (line[*i] != spec.keeper && line[*i])
	{
		if (line[*i] == 92)
		{
			spec.definer = 1;
			str = escape_character(str, line, &(*i), spec);
		}
		else if (line[*i] == '$' && line[(*i) + 1] == '(' && spec.keeper == '"')
		{
			get_set_holder(false, NULL)->error = ft_strdup("quoted");
			str = dollar_parenthesis(get_set_holder(false, NULL), str, i);
		}
		else
			str = ft_joinchar(str, line[*i]);
		(*i)++;
	}
	str = ft_joinchar(str, line[*i]);
	return (str);
}

char	*nasty(char *line, char *str, int *i, int def)
{
	char		*tmp;

	if (def)
	{
		str = token_manager(str, line, &(*i));
		(*i)--;
	}
	else if (!def)
	{
		tmp = str;
		str = ignore_quote(str, 0);
		ft_strdel(&tmp);
	}
	return (str);
}

char	*parse_within(char *line, char *str, int *i, t_quote spec)
{
	if (ft_isquote(line[*i]))
		str = quote_treatement(line, str, &(*i), spec);
	else if (seperators_check(line[*i], line[(*i) + 1]))
		seperators_parse(line, &str, i);
	else if (((ft_isdigit(line[*i])
					&& got_token_after_digit(line + (*i)))
				|| ft_istoken(line[*i])) && line[*i])
		str = nasty(line, str, &(*i), 1);
	else if (line[*i] == ';')
	{
		str = ft_joinchar(str, SEPERATOR);
		str = ft_joinchar(str, line[*i]);
		str = ft_joinchar(str, SEPERATOR);
	}
	else if (line[*i] == '|')
		str = ft_joinchar(str, -4);
	else
		str = ft_joinchar(str, line[*i]);
	return (str);
}

char	*terminator(char *line, char **str)
{
	*str = ft_strdup("");
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

char	*parsin(t_holder *h)
{
	int			i;
	t_quote		spec;
	char		*str;

	i = 0;
	spec.env = h->head_ref;
	h->line = terminator(h->line, &str);
	if (!h->line)
		return (NULL);
	while (h->line[i] && i < (int)ft_strlen(h->line))
	{
		if (h->line[i] == 92)
			str = escape_character(str, h->line, &i,
				(t_quote){0, 0, h->head_ref});
		else if (h->line[i] == '$' && h->line[i + 1] == '(')
			str = dollar_parenthesis(h, str, &i);
		else if (h->interactive && h->line[i] == '\n')
			str = ft_joinchar(str, -3);
		else
			str = parse_within(h->line, str, &i, spec);
		i++;
	}
	str = nasty(h->line, str, &i, 0);
	return (str);
}
