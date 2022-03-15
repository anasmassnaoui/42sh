/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 13:37:35 by aariss            #+#    #+#             */
/*   Updated: 2018/10/14 13:43:19 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	char	*s;

	if (!(s = (char*)malloc(sizeof(char) * n + 1)))
		return (0);
	s = ft_strncpy(s, str, n);
	s[n] = '\0';
	return (s);
}
