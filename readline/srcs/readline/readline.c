/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 17:06:28 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/02/15 18:15:36 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "auto.h"

int			ctrl_d_handler(t_line *line)
{
	char *tmp;

	if ((ft_strcmp(line->prompt, "$> ") == 0) &&
			(ft_strlen(line->str) == 0) && (ft_strlen(line->cmd) == 0))
	{
		line->cmd = ft_joinchar_glob(line->cmd, -6);
		return (-1);
	}
	else if ((ft_strcmp(line->prompt, "heredoc> ") == 0))
	{
		tmp = line->cmd;
		line->cmd = ft_joinchar_glob(ft_strdup(line->str), -8);
		ft_strdel(&tmp);
		return (-1);
	}
	return (0);
}

static void	init_readline(t_line *line, t_all_hist *hist, t_env *head_ref)
{
	print_prompt(line->prompt);
	init_histrory(hist, line->prompt);
	get_en_rl(line, head_ref);
	line->env = head_ref;
	get_set_line(0, line);
	signal(SIGWINCH, winresize);
}

char		*readline(char *prompt)
{
	int					buff;
	static t_all_hist	hist;
	t_env				*head_ref;
	struct termios		term;

	prepare_path(&hist);
	head_ref = get_set_holder(false, NULL)->head_ref;
	term = get_set_holder(false, NULL)->term;
	prepare_termcap(term);
	MAD_DECLARE(t_line, line, initial_line(prompt));
	init_readline(&line, &hist, head_ref);
	while (1337)
	{
		buff = 0;
		read(0, &buff, 4);
		if (signals(&line) == -1)
			break ;
		if (ctrl_d(&line, buff) == 1)
			break ;
		if (check_arrow(&line, buff, &hist) == -1)
			break ;
	}
	free_line(line);
	return (line.cmd);
}

void		free_line(t_line line)
{
	ft_strdel(&line.str);
	ft_strdel(&line.tmp_str);
	ft_strdel(&line.copy);
	ft_strdel(&line.home);
	ft_strdel(&line.path);
	ft_strdel(&line.prompt);
	ft_strdel(&line.result);
}
