/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:27:31 by aariss            #+#    #+#             */
/*   Updated: 2018/10/21 12:19:32 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		len_s;
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (!(str = ft_strnew(len_s)))
		return (NULL);
	i = 0;
	while (f && s[i])
	{
		str[i] = f(s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
