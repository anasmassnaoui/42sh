/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suggestion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 17:34:27 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/02/06 21:43:22 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"

void			check_tab_and_mode(t_line *line)
{
	char	*path;
	char	**paths;
	t_names	*sugg;
	t_names	*tmp;

	sugg = NULL;
	tmp = NULL;
	(*line).mode_auto = 1;
	if ((*line).mode_search == 1 || (*line).mode_search == 2)
	{
		path = ft_strdup((*line).path);
		paths = get_path_autocmp(path);
		(*line).names = check_tab_path(line, paths, sugg, tmp);
		free_2d(paths);
		ft_strdel(&path);
	}
	else
		(*line).names = check_tab(line, sugg, tmp);
	display_first_time(line);
}

static int		verify_hint(char *hint, char *name, int len)
{
	char *tmp_hint;
	char *tmp_name;

	if (len > 0)
	{
		tmp_hint = min_all(hint);
		tmp_name = min_all(name);
		if (ft_strncmp(hint, name, len) == 0 ||
				ft_strncmp(tmp_hint, name, len) == 0 ||
				ft_strncmp(hint, tmp_name, len) == 0)
		{
			ft_strdel(&tmp_hint);
			ft_strdel(&tmp_name);
			return (0);
		}
		ft_strdel(&tmp_hint);
		ft_strdel(&tmp_name);
	}
	return (1);
}

void			check_tab_bis(t_line *l, t_names **s, t_names **t, int len)
{
	struct dirent	*contenu;
	DIR				*rep;

	if ((rep = opendir((*l).ground)) != NULL)
	{
		while ((contenu = readdir(rep)))
		{
			if (len > 0)
			{
				if (verify_hint((*l).hint, contenu->d_name, len) == 0)
					get_suugestion(contenu->d_name, l->ground, t, s);
			}
			else
			{
				if (contenu->d_name[0] != '.')
					get_suugestion(contenu->d_name, l->ground, t, s);
			}
		}
		closedir(rep);
	}
}

t_names			*check_tab(t_line *line, t_names *sugg, t_names *tmp)
{
	int				len;

	len = ft_strlen((*line).hint);
	if ((*line).mode_search == 1 || (*line).mode_search == 0)
		check_tab_bis(line, &sugg, &tmp, len);
	if ((*line).mode_search == 2 || (*line).mode_search == 1)
		sugg = get_env_vars(line, sugg, tmp);
	return (sort_list_ascci(sugg));
}

t_names			*check_tab_path(t_line *l, char **p, t_names *s, t_names *t)
{
	struct dirent	*contenu;
	DIR				*rep;
	int				j;
	int				len;

	j = 0;
	len = ft_strlen((*l).hint);
	if (l->mode_search != 2)
	{
		while (p[j])
		{
			if (access(p[j], F_OK) == 0)
			{
				if ((rep = opendir(p[j])) != NULL)
					while ((contenu = readdir(rep)))
					{
						if (verify_hint(l->hint, contenu->d_name, len) == 0)
							get_suugestion(contenu->d_name, l->ground, &t, &s);
					}
				closedir(rep);
			}
			j++;
		}
	}
	return (after_check(l, s, t));
}
