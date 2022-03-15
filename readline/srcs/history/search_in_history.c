/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:44:19 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/15 18:31:51 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int			count_index(char *ptr)
{
	int		i;

	i = 0;
	while (ptr[i])
	{
		if (ptr[i] != ' ')
			i++;
		else
			return (i);
	}
	return (0);
}

int			count_file_lines(t_all_hist *history)
{
	int		i;
	char	*ptr;
	int		count;

	if (!history->fp)
		return (0);
	count = 0;
	ptr = NULL;
	while (get_next_line(history->fp, &ptr, -2) > 0)
	{
		i = count_index(ptr) + 1;
		store_line(history, ptr + i);
		count++;
		ft_strdel(&ptr);
	}
	ft_strdel(&ptr);
	return (count);
}

void		s_file(t_all_hist *history, char *str)
{
	char	*tmp;

	tmp = ft_itoa(history->num);
	history->fp = open(history->path, O_RDWR
	| O_CREAT | O_APPEND, S_IRWXU);
	ft_putstr_fd(tmp, history->fp);
	ft_putchar_fd(' ', history->fp);
	ft_putendl_fd(str, history->fp);
	ft_putchar_fd(-2, history->fp);
	close(history->fp);
	ft_strdel(&tmp);
	history->num++;
}

void		check_fc(char *str, t_all_hist *history)
{
	char	**ptr;
	int		i;

	i = 0;
	ptr = ft_strsplit(str, ' ');
	while (ptr[i])
	{
		if (!ft_strcmp(ptr[i], "fc"))
		{
			history->x = 1;
			ft_free_tab2(ptr);
			return ;
		}
		i++;
	}
	ft_free_tab2(ptr);
}

void		store_in_file(char *str, t_all_hist *history)
{
	int		i;

	i = ft_strlen(str);
	if (str && i > 0 && str[i - 1] == '\n')
		str[i - 1] = '\0';
	else
		str[i] = '\0';
	check_fc(str, history);
	if (history->x == 1)
		return ;
	if (str && check_white_spaces(str))
	{
		if (!history->lst || ft_strcmp(str, history->tmp->history))
			s_file(history, str);
	}
}
