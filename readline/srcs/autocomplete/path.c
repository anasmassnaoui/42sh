/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 17:27:55 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/06 13:14:20 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"

char	**get_path_autocmp(char *path)
{
	char **splitpath;

	splitpath = ft_strsplit(path, ':');
	return (splitpath);
}

char	*trim_equal(char *str)
{
	char **tmp;
	char *one_tmp;

	tmp = ft_strsplit(str, '=');
	one_tmp = ft_strdup(tmp[0]);
	free_2d(tmp);
	return (one_tmp);
}

char	*min_all(char *s1)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = malloc(sizeof(char) * ft_strlen(s1) + 1);
	while (s1[i] != '\0')
	{
		tmp[i] = ft_toupper(s1[i]);
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	display_first_time(t_line *line)
{
	if ((*line).names)
	{
		display_sugg(line);
		(*line).names->active = 1;
	}
	else
	{
		ft_strdel(&line->ground);
		ft_strdel(&line->hint);
		tputs(tgetstr("bl", NULL), 1, my_putchar);
		(*line).mode_auto = 0;
	}
}
