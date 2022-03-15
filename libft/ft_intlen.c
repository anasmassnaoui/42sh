/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 16:16:45 by aariss            #+#    #+#             */
/*   Updated: 2018/12/20 13:36:02 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_intlen(int n)
{
	int		countnumber;

	if (n == 0)
		return (1);
	countnumber = 0;
	if (n < 0)
		n = n * 10;
	while (n)
	{
		n = n / 10;
		++countnumber;
	}
	return (countnumber);
}
