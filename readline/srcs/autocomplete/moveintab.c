/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moveintab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:41:57 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/28 17:03:24 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"

static char	*trim_part_from_str(char *str, int curs, int len)
{
	char	*newstr;
	int		i;
	int		j;

	newstr = malloc(sizeof(char) * ((ft_strlen(str) - len) + 1));
	i = 0;
	while (i < (curs - len))
	{
		newstr[i] = str[i];
		i++;
	}
	j = curs;
	while (j < (int)ft_strlen(str))
	{
		newstr[i] = str[j];
		i++;
		j++;
	}
	newstr[i] = '\0';
	ft_strdel(&str);
	return (newstr);
}

void		clean_window(t_line *line)
{
	tputs(tgetstr("vi", 0), 0, my_putchar);
	tputs(tgoto(tgetstr("cm", NULL), (*line).msg_size, (*line).my_in - 1),
			1, my_putchar);
	tputs(tgetstr("cd", 0), 0, my_putchar);
}

void		move_tab_tree(t_line *line, int k)
{
	(*line).str = trim_part_from_str((*line).str, (*line).curs, k);
	ft_strdel(&(*line).hint);
	(*line).hint = ft_strdup("");
	(*line).curs = (*line).curs - k;
}

void		move_tab_bus(t_line *line, char *name)
{
	int		k;
	char	*newtmp;
	char	**tmp;
	int		j;

	newtmp = NULL;
	line->first_time = 1;
	k = ft_strlen((*line).hint);
	tmp = ft_strsplit(name, '/');
	j = count_list(tmp);
	if (verify_type(name) == 1)
		newtmp = ft_strjoin(tmp[j - 1], "/");
	else
		newtmp = ft_strdup(tmp[j - 1]);
	free_2d(tmp);
	if (k != 0)
		move_tab_tree(line, k);
	ft_strdel(&line->tmp_str);
	(*line).tmp_str = join_two_chars((*line).str, newtmp, (*line).curs);
	ft_putstr_fd((*line).tmp_str, 0);
	pos_curs_tab(line, newtmp);
	display_sugg_move(line);
	(*line).curs = (*line).curs - ft_strlen(newtmp);
	tputs(tgetstr("ve", 0), 0, my_putchar);
	ft_strdel(&newtmp);
}

void		move_tab(t_line *line, t_names *sugg)
{
	t_names	*head;

	head = sugg;
	while (sugg)
	{
		if (sugg->active == 1)
		{
			clean_window(line);
			move_tab_bus(line, sugg->name);
			if (sugg->next == NULL)
			{
				sugg->active = 0;
				(*line).tmp_curs = 1;
				head->active = 1;
				break ;
			}
			sugg->next->active = 1;
			sugg->active = 0;
			break ;
		}
		sugg = sugg->next;
	}
	(*line).tmp_curs++;
}
