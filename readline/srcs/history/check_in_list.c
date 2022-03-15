/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 20:16:17 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/13 18:11:43 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void			double_excl(char **ptr, t_history *lst, int *t)
{
	t_history	*tmp;
	char		*tmp_2;

	tmp = lst;
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			tmp_2 = *ptr;
			*ptr = ft_strjoin(tmp->history, *ptr + 2);
			ft_strdel(&tmp_2);
			*t = 1;
			return ;
		}
		else
		{
			tmp = tmp->next;
			*t = 0;
		}
	}
}

void			error_msg(char *ptr, int t)
{
	char		*tmp_2;

	tmp_2 = ft_strjoin("42sh: no such event: ", ptr + t);
	ft_putendl(tmp_2);
	ft_strdel(&tmp_2);
}

void			single_excl(char **ptr, t_history *lst, int *t)
{
	t_history	*tmp;
	char		*tmp_2;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strncmp(*ptr + 1, tmp->history, ft_strlen(*ptr + 1))
		|| ft_atoi(*ptr + 1) == tmp->nb)
		{
			tmp_2 = *ptr;
			*ptr = tmp->history;
			ft_strdel(&tmp_2);
			*t = 1;
			break ;
		}
		else
		{
			tmp = tmp->next;
			*t = 0;
		}
	}
	if (*t == 0)
		error_msg(*ptr, 1);
}

void			last_of_list(char **ptr, t_history *lst, int *t)
{
	int			res;
	int			i;
	char		*tmp_2;

	i = 0;
	res = len_list(lst) - ft_atoi(*ptr + 2);
	while (lst && res > 0)
	{
		if (i == res)
		{
			tmp_2 = *ptr;
			*ptr = lst->history;
			ft_strdel(&tmp_2);
			*t = 1;
			return ;
		}
		else
		{
			*t = 0;
			lst = lst->next;
			i++;
		}
	}
	if (*t == 0)
		error_msg(*ptr, 2);
}

char			*get_char_from_hist(t_history *lst, char *substr)
{
	while (lst)
	{
		if (ft_strstr(lst->history, substr) != 0)
			return (lst->history);
		else
			lst = lst->next;
	}
	return (0);
}
