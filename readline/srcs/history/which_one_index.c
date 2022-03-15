/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_one_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:12:09 by mhouiri           #+#    #+#             */
/*   Updated: 2020/01/23 14:12:43 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int				hist_index(t_history *tm, char *ptr)
{
	while (tm)
	{
		if (!ft_strncmp(tm->history, ptr, ft_strlen(ptr)))
			return (tm->nb);
		else
			tm = tm->next;
	}
	return (0);
}

int				which_one(t_history *cmd, char *ptr)
{
	if (ft_atoi(ptr))
		return (ft_atoi(ptr));
	if (hist_index(cmd, ptr))
		return (hist_index(cmd, ptr));
	else
		return (0);
}
