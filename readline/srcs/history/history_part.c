/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 18:07:24 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/15 18:17:22 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "auto.h"

void		prepare_path(t_all_hist *history)
{
	char	*home_login;

	if (history->path)
		return ;
	home_login = ft_strjoin("/Users/", getlogin());
	history->path = ft_strjoin(home_login, "/.history");
	ft_strdel(&home_login);
}

int			check_line(char *prompt, t_line *line)
{
	if ((*line).cmd && check_white_spaces((*line).cmd)
			&& (ft_strcmp(prompt, "heredoc> "))
			&& (ft_strcmp(prompt, "cmdsubst> ")))
		return (1);
	return (0);
}

void		history_part(t_line *line, t_all_hist *history)
{
	char	*tmp_hist;
	char	**tab_env;
	int		i;

	i = 0;
	shell_s(history, (*line).prompt, (*line).cmd);
	if (check_line((*line).prompt, line))
	{
		tmp_hist = ft_strdup((*line).cmd);
		if (tmp_hist && (i = ft_strlen(tmp_hist)) > 0
				&& tmp_hist[i - 1] == '\n')
			tmp_hist[i - 1] = '\0';
		if (ft_strstr(tmp_hist, "!!") || ft_strstr(tmp_hist, "!-")
				|| ft_strstr(tmp_hist, "!"))
			tmp_hist = check_in_list(tmp_hist, history);
		tab_env = get_envv(line->env);
		store_in_file(tmp_hist, history);
		store_line(history, tmp_hist);
		ft_strdel(&(*line).cmd);
		(*line).cmd = ft_strdup(tmp_hist);
		ft_strdel(&tmp_hist);
		ft_free_tab2(tab_env);
	}
}

void		display_history_up(t_all_hist *history, t_line *line)
{
	char	*tmp;
	int		b;

	tmp = up_key(history);
	if (tmp && ft_strlen(tmp))
	{
		go_home(line);
		ft_strdel(&(*line).str);
		(*line).str = ft_strdup(tmp);
		tputs(tgetstr("cd", NULL), 1, my_putchar);
		ft_putstr_fd((*line).str, 1);
		(*line).curs = ft_strlen((*line).str);
		b = get_count_line(line);
		if ((*line).my_in == (*line).row)
			(*line).my_in -= b - 1;
	}
}

void		display_history_down(t_all_hist *history, t_line *line)
{
	char	*tmp;
	int		b;

	tmp = down_key(history);
	if (tmp)
	{
		go_home(line);
		ft_strdel(&(*line).str);
		(*line).str = ft_strdup(tmp);
		tputs(tgetstr("cd", NULL), 1, my_putchar);
		ft_putstr_fd((*line).str, 1);
		(*line).curs = ft_strlen((*line).str);
		b = get_count_line(line);
		if ((*line).my_in == (*line).row)
			(*line).my_in -= b - 1;
	}
}
