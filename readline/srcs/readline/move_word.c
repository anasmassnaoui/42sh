/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:58:43 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/04 13:28:52 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	move_right(t_line *line)
{
	int i;

	i = (*line).curs;
	while ((*line).str[i] && (ft_isalnum((*line).str[i])))
	{
		i++;
		go_right(line);
	}
	while ((*line).str[i] && !(ft_isalnum((*line).str[i])))
	{
		i++;
		go_right(line);
	}
}

void	move_left(t_line *line)
{
	int i;

	i = (*line).curs;
	while (i > 0 && !(ft_isalnum((*line).str[i - 1])))
	{
		go_left(line);
		i--;
	}
	while (i > 0 && (ft_isalnum((*line).str[i - 1])))
	{
		go_left(line);
		i--;
	}
}
