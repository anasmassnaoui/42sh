/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:14:25 by aariss            #+#    #+#             */
/*   Updated: 2020/02/01 13:37:48 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsin.h"

int		is_a_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
			|| ft_strcmp(cmd, "jobs") == 0
			|| ft_strcmp(cmd, "alias") == 0
			|| ft_strcmp(cmd, "fc") == 0
			|| ft_strcmp(cmd, "unalias") == 0
			|| ft_strcmp(cmd, "type") == 0
			|| ft_strcmp(cmd, "unset") == 0
			|| ft_strcmp(cmd, "which") == 0
			|| ft_strcmp(cmd, "exit") == 0
			|| ft_strcmp(cmd, "fg") == 0
			|| ft_strcmp(cmd, "bg") == 0
			|| ft_strcmp(cmd, "export") == 0
			|| ft_strcmp(cmd, "set") == 0
			|| (cmd && is_toset(cmd))
			|| ft_strcmp(cmd, "hash") == 0)
		return (1);
	return (0);
}

char	*ft_strfchr_alpha(char *s)
{
	char	*str;
	size_t	i;

	if (!(str = (char*)malloc(sizeof(char) * (ft_count_falpha(s) + 1))))
		return (0);
	i = 0;
	while (s[i] && ft_isalpha(s[i]))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strfchr(char *s, int c)
{
	char	*str;
	size_t	i;

	if (!(str = (char*)malloc(sizeof(char) * (ft_count_till(s, c) + 1))))
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*container(char *s, char c)
{
	char	*str;
	int		s_size;
	int		i;

	s_size = ft_strlen(s);
	if (!(str = (char*)malloc(sizeof(char) * (s_size + 2))))
		return (0);
	i = 0;
	if (s)
	{
		while (s[i])
		{
			str[i] = s[i];
			i++;
		}
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}

char	*ft_joinchar(char *s, char c)
{
	char *tmp;

	tmp = s;
	s = container(s, c);
	ft_strdel(&tmp);
	return (s);
}
