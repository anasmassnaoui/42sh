/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generale_auto.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 17:10:39 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/04 17:11:10 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"

int		maxlen(t_names *names)
{
	int i;

	i = 0;
	while (names)
	{
		if (i < (int)ft_strlen(names->name))
			i = (int)ft_strlen(names->name);
		names = names->next;
	}
	return (i);
}

int		count_sugg(t_names *names)
{
	int		i;
	t_names	*tmp;

	i = 0;
	tmp = names;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int		count_list(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

void	print_prompt1(char *prompt)
{
	ft_putstr(COLOR2);
	ft_putstr(prompt);
	ft_putstr(RESET2);
}
