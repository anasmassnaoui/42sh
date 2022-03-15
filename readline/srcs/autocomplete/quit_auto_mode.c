/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_auto_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 17:28:55 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/02/06 21:44:45 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto.h"

static void	restaure_modes(t_line *line)
{
	(*line).mode_auto = 0;
	(*line).mode_search = 0;
}

void		restaur_curs(t_line *line)
{
	int old_curs;
	int i;

	old_curs = line->curs;
	tputs(tgoto(tgetstr("cm", NULL), line->msg_size, (*line).my_in - 1),
			1, my_putchar);
	i = 0;
	line->curs = 0;
	while (i < old_curs)
	{
		go_right(line);
		i++;
	}
}

void		quit_mode_auto(t_line *line)
{
	int i;

	if ((*line).mode_auto == 1)
	{
		i = -1;
		restaure_modes(line);
		if (ft_strlen((*line).tmp_str) != 0)
		{
			go_home(line);
			tputs(tgoto(tgetstr("cm", NULL),
						(*line).msg_size, (*line).my_in - 1), 1, my_putchar);
			tputs(tgetstr("cd", NULL), 1, my_putchar);
			ft_strdel(&(*line).str);
			(*line).str = ft_strdup("");
			while ((*line).tmp_str[++i] != '\0')
				display_str(line, (*line).tmp_str[i]);
			(*line).curs = (*line).last_curs_pos;
			restaur_curs(line);
			line->first_time = 0;
			line->first_auto = 0;
		}
		else
			line->first_auto = 1;
		free_mode_auto(line);
	}
}

void		free_mode_auto(t_line *line)
{
	ft_strdel(&line->hint);
	ft_strdel(&line->ground);
	ft_strdel(&line->tmp_str);
	free_liste_mode_auto(line->names);
}

void		free_liste_mode_auto(t_names *liste)
{
	t_names *todel;

	while (liste)
	{
		ft_strdel(&liste->name);
		todel = liste;
		liste = liste->next;
		free(todel);
	}
}
