/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:21:27 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/28 15:21:39 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globing.h"

char	*container_glob(char *s, char c)
{
	char	*str;
	int		s_size;
	int		i;

	s_size = ft_strlen(s);
	if (!(str = (char*)malloc(sizeof(char) * (s_size + 2))))
		return (0);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}

char	*ft_joinchar_glob(char *s, char c)
{
	char *tmp;

	tmp = s;
	s = container_glob(s, c);
	ft_strdel(&tmp);
	return (s);
}
