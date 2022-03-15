/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_suite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:39:58 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/04 13:19:40 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	display_copy(t_line *line)
{
	int i;

	go_home(line);
	tputs(tgetstr("sc", NULL), 1, my_putchar);
	tputs(tgetstr("cd", NULL), 1, my_putchar);
	i = (*line).curs;
	tputs(tgetstr("vi", NULL), 1, my_putchar);
	while ((*line).str[i] != '\0')
	{
		ft_putchar((*line).str[i]);
		i++;
	}
	tputs(tgetstr("rc", NULL), 1, my_putchar);
	tputs(tgetstr("ve", NULL), 1, my_putchar);
	im_in_last_col(line);
}

char	*copy_tmp_in_str2(t_line *line)
{
	char	*new_str;
	int		len;

	(*line).mode_select = 0;
	len = ft_strlen((*line).str) + ft_strlen((*line).copy) + 1;
	new_str = malloc(sizeof(char) * len);
	return (new_str);
}

t_vars	initvars(void)
{
	t_vars	var;

	var.i = -1;
	var.j = -1;
	return (var);
}

void	copy_tmp_in_str(t_line *line)
{
	int		count;
	char	*new_str;
	t_vars	var;

	var = initvars();
	new_str = copy_tmp_in_str2(line);
	while (++var.i < (*line).curs)
		new_str[var.i] = (*line).str[var.i];
	count = var.i + ft_strlen((*line).copy);
	while (++var.j < (int)ft_strlen((*line).copy))
	{
		new_str[var.i] = (*line).copy[var.j];
		var.i++;
	}
	var.j = (*line).curs;
	while (var.j < (int)ft_strlen((*line).str))
	{
		new_str[var.i] = (*line).str[var.j];
		var.i++;
		var.j++;
	}
	new_str[var.i] = '\0';
	free((*line).str);
	(*line).str = new_str;
	display_copy1(line, count);
}

void	display_copy1(t_line *line, int count)
{
	int j;

	display_copy(line);
	j = 0;
	while (j < count)
	{
		go_right(line);
		j++;
	}
}
