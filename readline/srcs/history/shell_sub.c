/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 13:26:01 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/15 12:56:26 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void		join_to_last_node(t_all_hist *hist, char *prompt)
{
	char	*tmp;
	int		j;

	j = 0;
	if (hist->sub_str && ft_strcmp(prompt, "cmdsubst> "))
	{
		while (last_node(hist->lst)[j])
			j++;
		last_node(hist->lst)[j++] = '\n';
		tmp = hist->sub_str;
		hist->sub_str = ft_strjoin(last_node(hist->lst), hist->sub_str);
		ft_strdel(&tmp);
		hist->sub_str[ft_strlen(hist->sub_str) - 1] = '\0';
		edit_last_node(hist);
		ft_strdel(&hist->sub_str);
	}
}

void		init_histrory(t_all_hist *hist, char *prompt)
{
	if (hist->first == 0)
	{
		hist->fp = open(hist->path, O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
		hist->num = count_file_lines(hist) + 1;
		close(hist->fp);
		hist->first++;
	}
	hist->x = 0;
	hist->index = 0;
	hist->t = 0;
	join_to_last_node(hist, prompt);
}

void		shell_s(t_all_hist *history, char *prompt, char *str)
{
	char	*tmp;

	if (!ft_strcmp(prompt, "cmdsubst> "))
	{
		if (!history->sub_str)
			history->sub_str = ft_strdup("");
		tmp = history->sub_str;
		history->sub_str = ft_strjoin(history->sub_str, str);
		ft_strdel(&tmp);
	}
}
