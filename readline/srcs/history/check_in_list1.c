/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_in_list1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:51:06 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/13 14:43:09 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void			check_execl(char **ptr, t_all_hist *history, int *t)
{
	if (!ft_strcmp(*ptr, "!"))
		*t = 1;
	else if (!ft_strncmp(*ptr, "!!", 2))
		double_excl(ptr, history->lst, t);
	else if (!ft_strncmp(*ptr, "!-", 2))
		last_of_list(ptr, history->lst, t);
	else if (!ft_strncmp(*ptr, "!", 1))
		single_excl(ptr, history->lst, t);
}

void			p_in_line(char **line, char *ptr, int i, int t)
{
	char		*tmp;
	char		*tmp2;

	if (ptr && i > 0 && t == 1)
	{
		tmp = *line;
		*line = ft_strjoin(*line, " ");
		ft_strdel(&tmp);
	}
	if (ptr && t == 1)
	{
		tmp2 = *line;
		*line = ft_strjoin(*line, ptr);
		ft_strdel(&tmp2);
	}
}

char			*check_in_list(char *str, t_all_hist *history)
{
	char		**ptr;
	int			i;
	char		*line;
	int			t;

	line = ft_strdup("");
	i = 0;
	ptr = ft_strsplit(str, ' ');
	ft_strdel(&str);
	while (ptr[i])
	{
		t = 1;
		check_execl(&ptr[i], history, &t);
		p_in_line(&line, ptr[i], i, t);
		ft_strdel(&ptr[i]);
		i++;
	}
	ft_free_tab2(ptr);
	if (line)
		ft_putendl(line);
	return (line);
}
