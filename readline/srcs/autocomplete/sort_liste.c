/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_liste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 11:23:33 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/02/06 21:43:31 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"

t_names			*sort_list_ascci(t_names *names)
{
	t_names	*i;
	t_names	*j;
	char	*tmp;
	int		pos;

	i = names;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->name, j->name) > 0)
			{
				tmp = i->name;
				i->name = j->name;
				j->name = tmp;
				pos = i->pos;
				i->pos = j->pos;
				j->pos = pos;
			}
			j = j->next;
		}
		i = i->next;
	}
	return (names);
}

t_autocmp_draw	init_draw(t_line *line)
{
	t_autocmp_draw draw;

	draw.d = 0;
	draw.i = (*line).my_in + count_lines_str(line) - 1;
	draw.j = 0;
	return (draw);
}

t_autocmp_draw	init_draw_two(t_line *line)
{
	t_autocmp_draw draw;

	draw.d = 0;
	draw.i = (*line).my_in + count_lines(line) - 1;
	draw.j = 0;
	return (draw);
}

t_autocmp_draw	init_draw_glob(t_line *line)
{
	t_autocmp_draw draw;

	if (line->first_time == 0)
		draw = init_draw_two(line);
	else
		draw = init_draw(line);
	return (draw);
}

t_names			*get_env_vars(t_line *line, t_names *sugg, t_names *tmp)
{
	t_env	*current;
	char	*tmp_str;
	int		len;
	char	*tmp_hint;
	char	*tmp_sugg;

	current = (*line).env;
	len = ft_strlen((*line).hint);
	while (current)
	{
		tmp_str = ft_strdup(current->var);
		tmp_hint = min_all((*line).hint);
		tmp_sugg = min_all(tmp_str);
		if (ft_strncmp((*line).hint, tmp_str, len) == 0 ||
				ft_strncmp(tmp_hint, tmp_str, len) == 0 ||
				ft_strncmp((*line).hint, tmp_sugg, len) == 0)
			get_suugestion(tmp_str, (*line).ground, &tmp, &sugg);
		current = current->next;
		ft_strdel(&tmp_str);
		ft_strdel(&tmp_hint);
		ft_strdel(&tmp_sugg);
	}
	return (sugg);
}
