/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 12:05:25 by aariss            #+#    #+#             */
/*   Updated: 2020/01/21 17:02:49 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		count_lstgod(t_cmd *lst)
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

void	and_and_counter(char *line, int *i, int *len, int *count)
{
	if (line[*i] == '|' && line[(*i) + 1] == '|')
		len = 0;
	else if (++(*len) == 1)
		(*count)++;
}

int		count_special_case(char *line, char token)
{
	int i;
	int len;
	int count;

	i = 0;
	len = 0;
	count = 0;
	while (line[i])
	{
		if (ft_isquote(line[i]))
			i = avoid_quote(line, i, 0);
		if (token == -12)
			and_and_counter(line, &i, &len, &count);
		else
		{
			if (line[i] == token)
				len = 0;
			else if (++len == 1)
				count++;
		}
		i++;
	}
	return (count);
}
