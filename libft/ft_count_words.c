/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 09:14:52 by aariss            #+#    #+#             */
/*   Updated: 2018/10/19 14:54:24 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_words(char const *s, char c)
{
	int		len;
	int		number;

	len = 0;
	number = 0;
	while (*s)
	{
		if (*s == c)
			len = 0;
		else if (++len == 1)
			number++;
		s++;
	}
	return (number);
}
