/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hint_and_dirs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:21:52 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/02/15 17:18:53 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"

char	*get_splited_word_globing(char *wild, char key)
{
	int i;
	int c;

	i = ft_strlen(wild);
	c = ft_strlen(wild);
	if (c != (int)ft_strlen(wild))
		c--;
	while (c >= 0 && wild[c] != key)
		c--;
	if (c != (int)ft_strlen(wild))
		return (ft_strsub(wild, c + 1, i - (c + 1)));
	else
		return (ft_strsub(wild, c + 1, i - c));
}

t_map	get_ground_hint_globing(char *wild)
{
	char	*ground;
	int		c;
	t_map	map;

	ground = ft_strdup(wild);
	if (ft_strchr(wild, '/'))
	{
		ft_strdel(&ground);
		map.hint = get_splited_word_globing(wild, '/');
		c = ft_strlen(wild) - ft_strlen(map.hint);
		wild[c] = '\0';
		map.directory = ft_strdup(wild);
	}
	else
	{
		map.directory = ft_strdup(".");
		map.hint = ground;
	}
	map.type_hint = verify_type_of(map.hint);
	return (map);
}

int		verify_type_of(char *hint)
{
	if (ft_strcmp(hint, "*") == 0)
		return (0);
	if (hint[0] == '*')
		return (1);
	if (hint[0] != '*' && hint[ft_strlen(hint) - 1] != '*')
		return (2);
	if (hint[ft_strlen(hint) - 1] == '*')
		return (3);
	return (-1);
}

int		wild_found(char *str, int curs)
{
	int i;

	i = 0;
	while (i < curs)
	{
		if (is_wild(str[i]))
			return (1);
		i++;
	}
	return (0);
}
