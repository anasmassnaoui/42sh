/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_e.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 21:04:33 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/15 15:58:11 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

void		fs_e_execution(char *cmd, char **flag, char **tab_env)
{
	t_holder	*h;
	char		*tmp;
	t_bool		background;

	h = get_set_holder(false, 0);
	while (ft_tcgetpgrp(0) != getpgrp())
		kill(getpgrp(), SIGSTOP);
	tmp = h->line;
	h->line = ft_strdup(cmd);
	ft_strdel(&tmp);
	(h->background) ? h->pid_42sh = 1 : 0;
	h->lst = NULL;
	create_group(h, getpid(), h->line);
	h->current_groupe = h->groups;
	background = h->background;
	h->background = false;
	execute_handler(cmd, flag, tab_env, h);
	ft_tcsetpgrp(0, h->groups->pgid);
	monitor_process(h->groups, h->groups->process, true, false);
	ft_tcsetpgrp(0, h->pid_42sh);
	if (!background && !h->groups->process)
	{
		delete_group(h, NULL, h->groups, h->groups->pgid);
		h->current_groupe = h->groups;
	}
}

void		line_empty_free(char *line2, char **str)
{
	ft_strdel(&line2);
	*str = ft_strdup("");
}

void		put_cmd_in_file(char *cmd, char *path1)
{
	int fx;

	fx = open(path1, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR, S_IWUSR);
	ft_putstr_fd(cmd, fx);
	close(fx);
}

void		fc_e(char *ptr, char **str, char **tab_env, char *cmd)
{
	int		fx;
	char	**line;
	char	*line2;
	char	*path1;
	char	*path2;

	path1 = file_path();
	path2 = join_path(ptr);
	line = ft_strsplit(path2, ' ');
	fx = open(path1, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR, S_IWUSR);
	ft_putstr_fd(cmd, fx);
	fs_e_execution(line[0], line, tab_env);
	close(fx);
	fx = open(path1, S_IRUSR);
	if (get_next_line(fx, &line2, '\n') > 0)
	{
		ft_putendl(line2);
		*str = line2;
	}
	else
		line_empty_free(line2, str);
	close(fx);
	free_paths(line, path1, path2);
}

void		r_in_file(char **tab_env, char *last_word)
{
	int		fx;
	char	**line;
	char	*path1;
	char	*path2;

	path1 = file_path();
	path2 = join_path("vim");
	fx = open(path1, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	ft_putendl_fd(last_word, fx);
	line = ft_strsplit(path2, ' ');
	close(fx);
	fs_e_execution(line[0], line, tab_env);
	ft_free_tab2(line);
	ft_strdel(&path1);
	ft_strdel(&path2);
}
