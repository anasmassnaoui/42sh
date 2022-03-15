/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 18:43:56 by aariss            #+#    #+#             */
/*   Updated: 2020/01/17 18:58:47 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_f(char *s1, char *s2, int which_one)
{
	char	*tmp;
	char	*tempo;
	char	*output;

	output = NULL;
	tmp = NULL;
	if (which_one == 1)
	{
		tmp = s1;
		output = ft_strjoin(s1, s2);
	}
	else if (which_one == 2)
	{
		tmp = s2;
		output = ft_strjoin(s1, s2);
	}
	else if (which_one == 3)
	{
		tmp = s1;
		tempo = s2;
		output = ft_strjoin(s1, s2);
		ft_strdel(&tempo);
	}
	(tmp) ? ft_strdel(&tmp) : 0;
	return (output);
}
