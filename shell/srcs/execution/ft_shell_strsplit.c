/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_strsplit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 22:59:25 by aariss            #+#    #+#             */
/*   Updated: 2020/01/12 23:02:29 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_count_words_shell(char const *s, char c, char *confirm)
{
	int len;
	int number;
	int keeper;

	len = 0;
	number = 0;
	keeper = 0;
	while (*s)
	{
		if (*s == c)
			len = 0;
		else if (ft_strcmp(confirm, "YES") && ft_isquote(*s) && ++len)
		{
			if (*(s - 1) == c)
				number += 1;
			keeper = *s;
			s += 1;
			while (*s != keeper && *s)
				s += 1;
		}
		else if (++len == 1)
			number += 1;
		s += 1;
	}
	return (number);
}

int		skipper(char const *s, int i, char c, char *confirm)
{
	int keeper;

	keeper = 0;
	while (s[i] && s[i] != c)
	{
		if (ft_strcmp(confirm, "YES") == 0)
		{
			if (ft_isquote(s[i]))
			{
				keeper = s[i];
				i += 1;
				while (s[i] != keeper && s[i])
					i += 1;
			}
		}
		i += 1;
	}
	return (i);
}

char	**ft_shell_strsplit(char const *s, char c, char *confirm)
{
	int		len;
	int		i;
	int		j;
	int		s_len;
	char	**r;

	if (!s)
		return (0);
	s_len = ft_count_words_shell(s, c, confirm) + 1;
	if (!(r = (char **)malloc(sizeof(char *) * s_len)))
		return (0);
	i = 0;
	j = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i += 1;
		len = i;
		i = skipper(s, i, c, confirm);
		if (len < i)
			r[j++] = ft_strndup(s + len, i - len);
	}
	r[j] = NULL;
	return (r);
}
