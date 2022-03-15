/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:40:35 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/04 13:28:00 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "auto.h"

void	delete_char_two(t_line *line)
{
	quit_mode_auto(line);
	if ((*line).curs > 0)
	{
		go_left(line);
		tputs(tgetstr("sc", NULL), 1, my_putchar);
		(*line).str = delete_char(line);
		tputs(tgetstr("cd", NULL), 1, my_putchar);
		display_line(line);
		tputs(tgetstr("rc", NULL), 1, my_putchar);
	}
}

char	*delete_char(t_line *line)
{
	int		i;
	int		j;
	char	*s1;

	s1 = malloc(sizeof(char) * (ft_strlen((*line).str) + 1));
	i = 0;
	j = 0;
	while (i < (int)ft_strlen((*line).str))
	{
		if (j == (*line).curs)
		{
			j++;
			i--;
		}
		else
		{
			s1[i] = (*line).str[j];
			j++;
		}
		i++;
	}
	s1[i] = '\0';
	free((*line).str);
	return (s1);
}

void	*join_char(t_line *line, int buff)
{
	int		l;
	int		i;
	int		j;
	char	*s1;

	l = ft_strlen((*line).str) + 2;
	s1 = malloc(sizeof(char) * l);
	i = 0;
	j = 0;
	while (i < l - 1)
	{
		if (i == (*line).curs)
			s1[i] = buff;
		else
		{
			s1[i] = (*line).str[j];
			j++;
		}
		i++;
	}
	s1[i] = '\0';
	ft_strdel(&(*line).str);
	return (s1);
}

void	display_str(t_line *line, int buff)
{
	tputs(tgetstr("sc", NULL), 1, my_putchar);
	(*line).str = join_char(line, buff);
	tputs(tgetstr("cd", NULL), 1, my_putchar);
	display_line(line);
	tputs(tgetstr("rc", NULL), 1, my_putchar);
	if (buff == OK && (*line).my_in == (*line).row)
		go_up((*line).col);
	go_right(line);
	tputs(tgetstr("sc", NULL), 1, my_putchar);
	tputs(tgetstr("rc", NULL), 1, my_putchar);
}

void	display_line(t_line *line)
{
	int i;

	i = (*line).curs;
	while ((*line).str[i] != '\0')
	{
		ft_putchar((*line).str[i]);
		i++;
	}
}
