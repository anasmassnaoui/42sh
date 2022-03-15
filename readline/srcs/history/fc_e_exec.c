/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_e_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:32:13 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/16 20:37:28 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void		negative_args(t_history *lst, int fx, int start, int end)
{
	int i;

	i = 0;
	while (lst)
	{
		if (i >= start && i <= end)
		{
			ft_putendl_fd(lst->history, fx);
			lst = lst->next;
		}
		else
			lst = lst->next;
		i++;
	}
}

void		in_file(t_history *lst, int fx, int start, int end)
{
	if (start < 0 && end < 0)
	{
		start = start * -1;
		end = end * -1;
		if (start > end)
			negative_args(lst, fx, end, start);
		else if (end > start)
			negative_args(lst, fx, start, end);
		return ;
	}
	while (lst)
	{
		if (lst->nb >= start && lst->nb <= end)
		{
			ft_putendl_fd(lst->history, fx);
			lst = lst->next;
		}
		else
			lst = lst->next;
	}
}

void		many_args_exec(int fx, char **str)
{
	char	*tmp;
	char	*line2;
	char	*s1;

	while (get_next_line(fx, &line2, '\n') > 0)
	{
		s1 = ft_strjoin(line2, " ; ");
		tmp = *str;
		*str = ft_strjoin(*str, s1);
		ft_strdel(&s1);
		ft_strdel(&tmp);
		ft_strdel(&line2);
	}
	ft_strdel(&line2);
}

char		*p_file(t_history *lst, int start, int end, char **tab_env)
{
	int		fx;
	char	**line;
	char	*path1;
	char	*str;
	char	*path2;

	path1 = file_path();
	path2 = join_path("vim");
	str = ft_strdup("");
	fx = open(path1, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR, S_IWUSR);
	in_file(lst, fx, start, end);
	line = ft_strsplit(path2, ' ');
	fs_e_execution(line[0], line, tab_env);
	close(fx);
	fx = open(path1, S_IRUSR);
	many_args_exec(fx, &str);
	str[ft_strlen(str) - 3] = '\0';
	ft_free_tab2(line);
	close(fx);
	ft_strdel(&path1);
	ft_strdel(&path2);
	return (str);
}

char		*fc_e_args(t_history *tmp, char **ptr,
		t_history *cmd, char **tab_env)
{
	int		a;
	int		b;

	if (which_one(cmd, ptr[3]) && which_one(cmd, ptr[4]))
	{
		a = which_one(cmd, ptr[3]);
		b = which_one(cmd, ptr[4]);
		if (a < b)
			return (p_file(tmp, a, b, tab_env));
		else if (a > b)
			return (p_file(cmd, b, a, tab_env));
	}
	return (0);
}
