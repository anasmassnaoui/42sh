/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 13:19:35 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/15 15:25:12 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int				len_list(t_history *lst)
{
	int			i;
	t_history	*tmp_history;

	i = 0;
	tmp_history = lst;
	while (tmp_history != NULL)
	{
		tmp_history = tmp_history->next;
		i++;
	}
	return (i);
}

t_history		*get_history(char *str)
{
	t_history	*tmp;

	tmp = (t_history *)malloc(sizeof(t_history));
	tmp->history = ft_strdup(str);
	tmp->next = NULL;
	return (tmp);
}

void			store_head(t_history **tmp, char *str,
		t_history **lst, t_all_hist *history)
{
	int res;

	*tmp = get_history(str);
	res = 1;
	(*tmp)->nb = res;
	*lst = *tmp;
	get_set_holder(false, 0)->history = history;
}

void			store_last_cmd(t_all_hist *history, char *str)
{
	if (str && ft_strlen(str) && check_white_spaces(str))
	{
		if (ft_strcmp(history->tmp->history, str))
		{
			history->tmp->next = get_history(str);
			history->tmp = history->tmp->next;
			history->tmp->nb = len_list(history->lst);
		}
	}
}

void			store_line(t_all_hist *history, char *str)
{
	int			i;

	i = ft_strlen(str);
	if (history->x == 1)
	{
		history->x = 0;
		return ;
	}
	if (str && i > 0 && str[i - 1] == '\n')
		str[i - 1] = '\0';
	if (!history->lst)
	{
		if (str && ft_strlen(str) && check_white_spaces(str))
			store_head(&history->tmp, str, &history->lst, history);
	}
	else
		store_last_cmd(history, str);
}
