/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:27:39 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/02/15 17:34:08 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"

char	*color(char *name)
{
	struct stat	sts;
	int			i;

	i = lstat(name, &sts);
	if (i == -1)
		return (DEFAULT);
	if (S_ISREG(sts.st_mode))
		if (sts.st_mode & S_IXOTH)
			return (RED);
	if (S_ISDIR(sts.st_mode))
		return (CYAN);
	if (verify_type(name) == 3)
		return (PINK);
	return (DEFAULT);
}

int		display_name(char *str)
{
	char	**tmp;
	char	*newtmp;
	int		j;
	int		len;

	tmp = ft_strsplit(str, '/');
	j = count_list(tmp);
	if (verify_type(str) == 1)
		newtmp = ft_strjoin(tmp[j - 1], "/");
	else
		newtmp = ft_strdup(tmp[j - 1]);
	ft_putstr_fd(color(str), 0);
	ft_putstr_fd(newtmp, 0);
	ft_putstr_fd(DEFAULT, 0);
	free_2d(tmp);
	len = ft_strlen(newtmp);
	ft_strdel(&newtmp);
	return (len);
}

void	pos_curs_correctly(t_line *line)
{
	int a;
	int b;

	a = count_lines(line);
	b = (*line).curs + (*line).msg_size;
	if (b > (*line).col)
		b = b % (*line).col;
	tputs(tgoto(tgetstr("cm", NULL), b, (*line).my_in + a - 2), 1, my_putchar);
}

void	prepare_space_to_display(int t, t_line *line)
{
	int u;
	int k;

	u = -1;
	if ((*line).my_in + count_lines(line) + t > (*line).row &&
			(t + count_lines(line)) < (*line).row)
	{
		while (++u < t)
			tputs(tgetstr("sf", 0), 0, my_putchar);
		u = -1;
		k = ((*line).my_in + count_lines(line) + t) - (*line).row;
		while (++u < k - 1)
			(*line).my_in--;
		(*line).mode = 0;
	}
	else if (t + count_lines(line) > (*line).row)
	{
		tputs(tgetstr("cl", 0), 0, my_putchar);
		(*line).my_in = 1;
		print_prompt1("$> ");
		ft_putstr_fd((*line).str, 0);
		(*line).mode = 2;
	}
	else
		(*line).mode = 1;
}

void	display_sugg(t_line *line)
{
	int		t;
	int		col;
	int		max;
	t_names	*tmp;

	tmp = (*line).names;
	max = maxlen(tmp) + 1;
	col = (*line).col / max;
	if (((*line).col % max) != 0)
		col--;
	if (col == 0)
		col++;
	t = (count_sugg(tmp) / col);
	if ((count_sugg(tmp) % col) != 0)
		t++;
	prepare_space_to_display(t, line);
	if ((*line).mode == 2)
		move_in_modes_normal(line, max, col, (*line).row - 1);
	if ((*line).mode == 1 || (*line).mode == 0)
		move_in_modes_normal(line, max, col, t);
	restaur_curs(line);
}
