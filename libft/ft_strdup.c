/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 13:27:44 by aariss            #+#    #+#             */
/*   Updated: 2019/07/29 16:01:18 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*s2;
	size_t		s1_len;

	s1_len = ft_strlen(s1);
	if (!(s2 = ft_strnew(s1_len)))
		return (NULL);
	s2 = ft_strcpy(s2, s1);
	return (s2);
}
