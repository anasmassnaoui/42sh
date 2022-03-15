/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_suggestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:30:02 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/28 14:27:24 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"

t_names		*get_one_sugg(char *str, char *ground)
{
	t_names	*names;
	char	*tmp;

	names = (t_names *)malloc(sizeof(t_names));
	if (ft_strcmp(ground, ".") != 0)
		names->name = ft_strjoin(ground, str);
	else
		names->name = ft_strdup(str);
	if (verify_type(names->name) == 1)
	{
		tmp = names->name;
		names->name = ft_strjoin(tmp, "/");
		ft_strdel(&tmp);
	}
	else
	{
		tmp = names->name;
		names->name = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	names->active = 0;
	names->next = NULL;
	return (names);
}

void		get_suugestion(char *n, char *g, t_names **t, t_names **s)
{
	if (!*s)
	{
		*t = get_one_sugg(n, g);
		*s = *t;
	}
	else
	{
		(*t)->next = get_one_sugg(n, g);
		*t = (*t)->next;
	}
}

int			verify_type(char *name)
{
	struct stat	sts;
	int			i;

	i = lstat(name, &sts);
	if (i != 0)
		return (0);
	if (S_ISDIR(sts.st_mode))
		return (1);
	if (S_ISREG(sts.st_mode))
		return (2);
	if (S_ISLNK(sts.st_mode))
		return (3);
	if (S_ISCHR(sts.st_mode))
		return (4);
	if (S_ISSOCK(sts.st_mode))
		return (5);
	if (S_ISBLK(sts.st_mode))
		return (6);
	return (0);
}
