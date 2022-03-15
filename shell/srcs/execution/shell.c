/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 17:38:37 by aariss            #+#    #+#             */
/*   Updated: 2020/02/17 12:52:03 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		eval_command(t_holder *h, char **data)
{
	int		status;
	t_cmd	*valhala;

	valhala = last_splice(data, h->head_ref, h->aliases);
	h->lst = valhala;
	if (!cmd_list_check(valhala))
	{
		ft_putendl_fd("42sh: parse error", 2);
		free_main_lst(valhala);
		return (1);
	}
	status = -1;
	if (exit_status_expansion(-1) != 1)
	{
		if (ft_strcmp(valhala->cmd[0], "exit"))
			h->force_exit = false;
		status = darlin_g(h);
	}
	else
		exit_status_expansion(0);
	free_main_lst(valhala);
	return (status);
}

void	shell_execute(t_holder *h, int count)
{
	t__mc	*curr;
	int		x;

	x = 0;
	if (h->line[ft_strlen(h->line) - 1] == '\n')
		h->line[ft_strlen(h->line) - 1] = '\0';
	h->linecpyflag = 0;
	h->mclst = mc_maker(h);
	curr = h->mclst;
	if (!(count = count_mclst(curr)))
		return ;
	if (!ft_strcmp(h->error, "ctrl_c"))
	{
		ft_strdel(&h->line);
		free_list_mc(h->mclst);
		return ;
	}
	if (!parse_error_check(h))
	{
		ft_putendl_fd("42sh: parse error", 2);
		return ;
	}
	command_handler(h, false);
	free_list_mc(h->mclst);
}

char	*line_master(t_holder *h)
{
	char	*buffer;
	char	*res;
	char	*tmp;
	char	*line;
	int		rd;

	rd = 0;
	line = NULL;
	if (!h->interactive)
		line = readline("$> ");
	else
	{
		buffer = malloc(sizeof(char) * 1025);
		res = ft_strdup("");
		while ((rd = read(0, buffer, 1024)) > 0)
		{
			buffer[rd] = '\0';
			tmp = res;
			res = ft_strjoin(res, buffer);
			ft_strdel(&tmp);
			ft_strdel(&buffer);
		}
		line = res;
	}
	return (line);
}

void	sys_call(t_holder *h, struct termios term)
{
	if (h->messages)
	{
		show_messages(h->messages);
		h->messages = NULL;
	}
	h->line = line_master(h);
	tcsetattr(0, TCSANOW, &term);
	if (h->line[0] == -6)
	{
		ft_putchar('\n');
		exit_bastard(h, -666);
	}
	if (!syntax_checker(h->line))
		ft_putendl_fd("42sh: parse error", 2);
	else
		(!is_empty(h->line)) ? shell_execute(h, 0) : 0;
	ft_strdel(&h->line);
	ft_strdel(&h->error);
	reset_fds();
}

int		main(void)
{
	extern char		**environ;
	t_holder		*h;
	struct termios	term;
	char			*termtype;
	int				s;

	termtype = getenv("TERM");
	s = tgetent(0, termtype);
	tcgetattr(0, &term);
	verify_error(termtype, s);
	h = ft_memalloc(sizeof(t_holder));
	h->hash.count = 0;
	h->hash.size = SIZE_HASH;
	h->term = term;
	h->interactive = false;
	prepare_shell(&h, environ);
	while (42)
	{
		sys_call(h, term);
		if (h->interactive)
			exit(h->last_status);
	}
	return (0);
}
