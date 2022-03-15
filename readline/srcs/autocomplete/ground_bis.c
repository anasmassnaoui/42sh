/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ground_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 12:41:27 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/28 14:45:04 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"

static void	get_ground_hint_three(t_line *line)
{
	(*line).hint = ft_strdup("");
	(*line).ground = ft_strdup(".");
}

void		get_ground_hint_bis(t_line *line, char *ground)
{
	int c;

	if (ground[ft_strlen(ground) - 1] == '/')
	{
		ft_strdel(&line->ground);
		ft_strdel(&line->hint);
		(*line).ground = ground;
		(*line).hint = ft_strdup("");
	}
	else
	{
		ft_strdel(&line->hint);
		(*line).hint = get_splited_word(line, '/');
		c = ft_strlen(ground) - ft_strlen((*line).hint);
		ground[c] = '\0';
		ft_strdel(&line->ground);
		(*line).ground = ground;
	}
}

void		get_ground_hint_four(t_line *line, char *ground)
{
	if (ft_strcmp(ground, (*line).str) == 0)
		(*line).mode_search = 1;
	else if (ft_strncmp(ground, "${", 2) == 0)
	{
		if (ft_strlen(ground) > 2)
			(*line).hint = ft_strdup(ground + 2);
		else
			(*line).hint = ft_strdup("");
		(*line).mode_search = 2;
		ft_strdel(&ground);
	}
	else if (ft_strncmp(ground, "$", 1) == 0)
	{
		if (ft_strlen(ground) > 1)
			(*line).hint = ft_strdup(ground + 1);
		else
			(*line).hint = ft_strdup("");
		(*line).mode_search = 2;
		ft_strdel(&ground);
	}
}

void		get_ground_hint(t_line *line)
{
	char	*ground;

	ground = get_splited_word(line, ' ');
	ground = replace_tilde(ground, line->home);
	(*line).mode_search = 0;
	if (ft_strlen(ground) != 0)
	{
		if (ft_strchr(ground, '/'))
			get_ground_hint_bis(line, ground);
		else
		{
			ft_strdel(&line->ground);
			(*line).ground = ft_strdup(".");
			ft_strdel(&line->hint);
			(*line).hint = ground;
			get_ground_hint_four(line, ground);
		}
	}
	else
	{
		ft_strdel(&ground);
		get_ground_hint_three(line);
	}
}
