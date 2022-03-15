/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list_hist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 22:25:13 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/13 23:10:06 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int				check_white_spaces(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

void			edit_last_node(t_all_hist *hist)
{
	t_history	*tmp;
	char		*tmp2;

	tmp = hist->lst;
	while (tmp)
	{
		if (tmp->next == NULL)
		{
			tmp2 = tmp->history;
			tmp->history = ft_strdup(hist->sub_str);
			ft_strdel(&tmp2);
			tmp = tmp->next;
			return ;
		}
		tmp = tmp->next;
	}
}

void			free_paths(char **line, char *path1, char *path2)
{
	ft_free_tab2(line);
	ft_strdel(&path1);
	ft_strdel(&path2);
}

void			ft_free_tab2(char **p)
{
	int			i;

	i = 0;
	while (p[i])
		ft_strdel(&p[i++]);
	free(p);
	p = NULL;
}

void			free_list_hist(t_history **alst)
{
	t_history	*tmp;
	t_history	*list;

	list = *alst;
	while (list)
	{
		tmp = list->next;
		ft_strdel(&(list->history));
		free(list);
		list = tmp;
	}
	*alst = NULL;
}
