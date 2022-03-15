/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets_glob.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:56:33 by aariss            #+#    #+#             */
/*   Updated: 2020/01/28 15:56:38 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"

int		bracket_dash_match(char **string, char **hint)
{
	char	**range;
	int		r;
	int		v;

	v = 0;
	r = 0;
	range = range_maker(*hint);
	while (range[r])
	{
		if (**string >= *(range[r]) && **string <= *((range[r]) + 2))
			v = 1;
		r += 1;
	}
	if (v)
	{
		while (**hint && **hint != ']')
			*hint += 1;
		*hint += 1;
		*string += 1;
	}
	else
		return (0);
	return (1);
}

int		bracket_coma_match(char **string, char **hint)
{
	int		i;
	int		j;
	char	*tempo;
	char	*wild_substring;
	char	**keys;

	tempo = *hint;
	i = 0;
	while (**hint != ']' && **hint && (i += 1))
		*hint += 1;
	*hint += 1;
	wild_substring = ft_strndup(tempo + 1, i - 1);
	keys = ft_strsplit(wild_substring, ',');
	ft_strdel(&wild_substring);
	i = 0;
	j = 0;
	while (keys[i])
		if (**string == keys[i++][0] && (*string += 1))
			j = !j;
	ft_free2d(keys);
	if (!j)
		return (0);
	return (1);
}

int		bracket_reverse_char_match(char **string, char **hint)
{
	if (**string != *(*hint + 2))
	{
		while (**hint && **hint != ']')
			*hint += 1;
		*hint += 1;
		*string += 1;
	}
	else
		return (0);
	return (1);
}

int		bracket_one_char_match(char **string, char **hint)
{
	int t;

	t = 0;
	*hint += 1;
	while (**hint && **hint != ']')
	{
		if (**string == **hint)
			t = 1;
		*hint += 1;
	}
	if (t)
	{
		while (**hint && **hint != ']')
			*hint += 1;
		*hint += 1;
		*string += 1;
	}
	else
		return (0);
	return (1);
}

int		bracket_match(char **string, char **hint)
{
	if (*(*hint + 2) == '-')
	{
		if (!bracket_dash_match(string, hint))
			return (0);
	}
	else if (*(*hint + 2) == ',')
	{
		if (!bracket_coma_match(string, hint))
			return (0);
	}
	else if (*(*hint + 1) == '!')
	{
		if (!bracket_reverse_char_match(string, hint))
			return (0);
	}
	else
	{
		if (!bracket_one_char_match(string, hint))
			return (0);
	}
	return (1);
}
