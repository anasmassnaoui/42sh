/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:41:22 by aariss            #+#    #+#             */
/*   Updated: 2018/10/21 10:35:58 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char unsigned *p;

	p = (char unsigned *)s;
	while (n--)
	{
		if (*p != (unsigned char)c)
			p++;
		else
			return (p);
	}
	return (NULL);
}
