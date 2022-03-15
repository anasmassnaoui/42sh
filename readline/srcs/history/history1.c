/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 19:02:13 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/15 15:15:23 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

char			*nth_up(t_all_hist *history, t_history *tmp_hist)
{
	int			i;

	i = 0;
	if (history->index == 0)
		history->index = 0;
	else
		history->index--;
	while (tmp_hist != NULL)
	{
		if (i == history->index)
			return (tmp_hist->history);
		tmp_hist = tmp_hist->next;
		i++;
	}
	return (0);
}

char			*up_history(t_all_hist *history)
{
	t_history	*tmp_hist;

	tmp_hist = history->lst;
	if (history->t == 0)
	{
		history->index = len_list(tmp_hist) - 1;
		while (tmp_hist != NULL)
		{
			if (tmp_hist->next == NULL)
			{
				history->t = 1;
				return (tmp_hist->history);
			}
			else
				tmp_hist = tmp_hist->next;
		}
	}
	else
		return (nth_up(history, tmp_hist));
	return (0);
}

char			*down_history(t_all_hist *history)
{
	int			i;
	t_history	*tmp;

	tmp = history->lst;
	history->index++;
	i = 0;
	while (tmp != NULL)
	{
		if (i == history->index)
			return (tmp->history);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

char			*up_key(t_all_hist *history)
{
	if (history->index >= 0 && history->lst != NULL)
		return (up_history(history));
	return (NULL);
}

char			*down_key(t_all_hist *history)
{
	if (history->t == 0)
		return (NULL);
	else if (len_list(history->lst) == history->index + 1)
	{
		history->index++;
		return ("");
	}
	else if (history->lst != NULL && len_list(history->lst) > 1
	&& len_list(history->lst) > history->index + 1)
		return (down_history(history));
	return (NULL);
}
