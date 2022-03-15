/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 16:49:53 by aariss            #+#    #+#             */
/*   Updated: 2020/01/23 19:17:45 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		which_seperator(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '|'
			&& line[i] != '&' && line[i] != '>'
			&& line[i] != '<' && line[i] != ';')
	{
		i += 1;
	}
	return (line[i]);
}

int		reverse_check(char *line, int len)
{
	len -= 1;
	if (line[len] == ' ')
	{
		while (len > 0 && line[len] == ' ')
			len -= 1;
	}
	if ((line[len] == '&' && line[len - 1] == '&')
			|| (line[len] == '|' && line[len - 1] == '|')
			|| (line[len] == '&' && !ft_istoken(line[len - 1]))
			|| (line[len] == ';'))
	{
		return (1);
	}
	return (0);
}

void	alias_finder(t_holder *h, int *i, int *x)
{
	t_alias	*al;
	char	*before;
	char	*hint;
	char	*after;
	char	*first_merge;

	al = h->aliases;
	while (h->line[*i] && h->line[*i] == ' ')
		(*i) += 1;
	before = copy_till_index(h->line, *i);
	hint = ft_strfchr(h->line + *i, which_seperator(h->line + *i));
	after = copy_from_index(h->line, *i + ft_strlen(hint));
	while (al)
	{
		if (!ft_strcmp(al->alias, hint) && (*x = 1))
		{
			first_merge = ft_strjoin(before, al->original);
			h->line = ft_strjoin_f(first_merge, after, 1);
			i = i + ft_strlen(al->original);
			break ;
		}
		al = al->next;
	}
	al = h->aliases;
	free_alias_vars(before, hint, after);
}

void	alias_broker(t_holder *h, int *i, int *x)
{
	char	*tmp;

	tmp = NULL;
	if (*i == 0 || reverse_check(h->line, *i))
	{
		tmp = h->line;
		alias_finder(h, i, x);
		if (*x)
		{
			ft_strdel(&tmp);
			*x = 0;
		}
	}
}

void	alias_parse(t_holder *h)
{
	int		i;
	int		x;
	int		keeper;

	i = 0;
	x = 0;
	while (h->line[i])
	{
		if (ft_isalpha(h->line[i]))
			alias_broker(h, &i, &x);
		else if (ft_isquote(h->line[i]))
		{
			keeper = h->line[i];
			i += 1;
			while (h->line[i] && h->line[i] != keeper)
				i += 1;
		}
		i += 1;
	}
}
