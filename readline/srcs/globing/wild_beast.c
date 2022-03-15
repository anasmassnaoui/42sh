/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_beast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:25:06 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/28 15:36:53 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"

int			inside_bracket_check(const char *wild, int keeper, int cursor)
{
	char	*str;

	str = ft_strndup(wild + cursor + 1, keeper - cursor);
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '-' && *str != ',')
		{
			ft_strdel(&str);
			return (0);
		}
		str += 1;
	}
	ft_strdel(&str);
	return (1);
}

int			opened_bracket(const char *wild, int *cursor)
{
	int	keeper;

	*cursor -= 1;
	keeper = *cursor;
	while (*cursor >= 0 && wild[*cursor] && wild[*cursor] != '[')
	{
		if (wild[*cursor] == ']')
			return (0);
		(*cursor) -= 1;
	}
	if (wild[*cursor] == '[')
	{
		if (!inside_bracket_check(wild, keeper, *cursor))
			return (0);
	}
	else
		return (0);
	return (1);
}

t_map		map_create(const char *line, int count, int cursor, int end)
{
	t_map	edge;
	char	*wild;
	int		start;

	edge = init_map();
	if (count)
	{
		start = cursor;
		wild = ft_strsub(line, start + 1, end - start);
		edge = get_ground_hint_globing(wild);
		ft_strdel(&wild);
		edge.word_start = start;
		edge.word_end = end;
	}
	else
	{
		edge.word_end = 0;
		edge.word_start = 0;
	}
	return (edge);
}

t_map		get_wild(const char *line, int cursor)
{
	int		count;
	t_map	edge;
	int		end;

	edge = init_map();
	count = 0;
	while (line[cursor] == ' ')
		cursor--;
	end = cursor;
	while (cursor >= 0 && line[cursor] != ' ')
	{
		if (ft_isquote_glob(line[cursor]))
			cursor = wild_quote_skipper(line, cursor);
		if (is_wild(line[cursor]) || (line[cursor] == ']'
			&& is_valid_bracket(line, cursor)))
			count += 1;
		cursor -= 1;
	}
	edge = map_create(line, count, cursor, end);
	return (edge);
}

char		*wild_monkey(t_content *lst, char *line, t_map wild_map)
{
	char	*full_path;
	char	*first_line;
	char	*last_line;

	if (!lst || !line)
		return (NULL);
	first_line = copy_till_index(line, wild_map.word_start + 1);
	last_line = copy_from_index(line, wild_map.word_end + 1);
	while (lst)
	{
		if (ft_strcmp(wild_map.directory, ".") != 0)
			full_path = ft_strjoin_f(wild_map.directory, lst->name, 2);
		else
			full_path = lst->name;
		first_line = ft_strjoin_f(first_line, full_path, 3);
		if (lst->next != NULL)
			first_line = ft_joinchar_glob(first_line, ' ');
		lst = lst->next;
	}
	first_line = ft_strjoin_f(first_line, last_line, 3);
	return (first_line);
}
