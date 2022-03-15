/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:20:47 by aariss            #+#    #+#             */
/*   Updated: 2019/08/06 16:30:41 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsin.h"

int		count_accurance_unquoted(char *str, char c)
{
	int i;
	int count;
	int	keeper;

	i = 0;
	count = 0;
	keeper = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		else if (ft_isquote(str[i]))
		{
			keeper = str[i++];
			while (str[i] && str[i] != keeper)
				i++;
		}
		i++;
	}
	return (count);
}

int		count_mclst(t__mc *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int		count_tab(char **tableau)
{
	int i;

	i = 0;
	while (tableau[i])
		i++;
	return (i);
}

int		ft_count_falpha(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isalpha(s[i]))
		i++;
	return (i);
}

int		ft_count_till(char *s, int c)
{
	int i;

	i = 0;
	if (s)
		while (s[i] && s[i] != c)
		{
			i++;
		}
	return (i);
}
