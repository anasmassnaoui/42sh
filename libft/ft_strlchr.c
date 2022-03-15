/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 18:52:10 by aariss            #+#    #+#             */
/*   Updated: 2020/01/17 18:52:13 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlchr(const char *str, char c)
{
	int		i;
	int		j;
	char	*ptr;

	j = 0;
	i = (int)ft_strlen(str);
	while (i > 0 && str[i] != c)
		i -= 1;
	if (!(ptr = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (j <= i)
	{
		ptr[j] = str[j];
		j += 1;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*ft_strlchr_mod(const char *str, char c)
{
	int		i;
	int		j;
	char	*ptr;

	j = 0;
	i = (int)ft_strlen(str);
	while (i > 0 && str[i] != c)
		i -= 1;
	if (!(ptr = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		ptr[j] = str[j];
		j += 1;
	}
	ptr[j] = '\0';
	return (ptr);
}
