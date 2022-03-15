/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus_funct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:57:39 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/28 17:04:51 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"

t_names		*after_check(t_line *line, t_names *sugg, t_names *tmp)
{
	sugg = check_tab(line, sugg, tmp);
	return (sort_list_ascci(sugg));
}

void		pos_curs_tab(t_line *line, char *newtmp)
{
	(*line).curs = (*line).curs + ft_strlen(newtmp);
	(*line).last_curs_pos = (*line).curs;
}
