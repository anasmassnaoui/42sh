/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ground.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:33:42 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/28 14:28:23 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"

char		*get_lastword(t_line *line)
{
	int		i;
	char	*tmp;

	i = (*line).curs;
	while (i >= 0 && (*line).str[i] != ' ')
		i--;
	tmp = ft_strsub((*line).str, i + 1, (*line).curs - i);
	return (tmp);
}

char		*get_ground(t_line *line)
{
	int i;

	i = (*line).curs;
	if (i == 0)
		return (".");
	if ((*line).str[i - 1] == ' ')
		return (".");
	else if ((*line).str[i - 1] == '/')
		return (get_lastword(line));
	else if (ft_isprint((*line).str[i - 1]))
		return (get_lastword(line));
	else
		return (".");
	return (" ");
}

char		*get_splited_word(t_line *line, char key)
{
	int i;
	int c;

	i = (*line).curs;
	c = (*line).curs;
	if (c != (int)ft_strlen((*line).str))
		c--;
	while (c >= 0 && (*line).str[c] != key)
		c--;
	if (c != (int)ft_strlen((*line).str))
		return (ft_strsub((*line).str, c + 1, i - (c + 1)));
	else
		return (ft_strsub((*line).str, c + 1, i - c));
}

char		*get_splited_word_two(char *str, char key)
{
	int i;
	int c;

	i = ft_strlen(str);
	c = ft_strlen(str);
	if (c != (int)ft_strlen(str))
		c--;
	while (c >= 0 && str[c] != key)
		c--;
	if (c != (int)ft_strlen(str))
		return (ft_strsub(str, c + 1, i - (c + 1)));
	else
		return (ft_strsub(str, c + 1, i - c));
}

char		*replace_tilde(char *ground, char *home)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = malloc(sizeof(char) * (ft_strlen(home) + ft_strlen(ground)));
	i = -1;
	j = 2;
	if (ft_strncmp(ground, "~/", 2) == 0)
	{
		while (++i < (int)ft_strlen(home))
			tmp[i] = home[i];
		tmp[i] = '/';
		i++;
		while (j < (int)ft_strlen(ground))
		{
			tmp[i] = ground[j];
			j++;
			i++;
		}
		tmp[i] = '\0';
		ft_strdel(&ground);
		return (tmp);
	}
	ft_strdel(&tmp);
	return (ground);
}
