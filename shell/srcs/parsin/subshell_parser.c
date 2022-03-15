/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:15:24 by aariss            #+#    #+#             */
/*   Updated: 2020/01/28 17:01:08 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*look_elsewhere(char *line, int *i, char *str)
{
	int	keeper;

	keeper = line[*i];
	str = ft_joinchar(str, line[*i]);
	(*i) += 1;
	while (line[*i] && line[*i] != keeper)
	{
		str = ft_joinchar(str, line[*i]);
		(*i) += 1;
	}
	str = ft_joinchar(str, line[*i]);
	return (str);
}

char	*subshell_parser(char *line, int *i)
{
	char	*str;
	int		x;

	(*i) += 2;
	str = ft_strdup("");
	x = 0;
	while (line[*i])
	{
		if (line[*i] == ')' && !x)
			break ;
		else if (line[*i] == '$' && line[*i + 1] == '(')
			x += 1;
		else if (line[*i] == ')')
			x -= 1;
		if (ft_isquote(line[*i]))
			str = look_elsewhere(line, i, str);
		else
			str = ft_joinchar(str, line[*i]);
		(*i) += 1;
	}
	return (str);
}

char	*one_line(t_holder *h, int *fd)
{
	char			buffer[65501];
	unsigned long	size;
	char			*ptr;
	char			*tmp;

	size = read(fd[0], buffer, 65500);
	ptr = ft_strdup("");
	if (size > 0 && size < sizeof(buffer))
	{
		buffer[size] = '\0';
		ptr = ft_strjoin_f(ptr, buffer + 1, 1);
	}
	tmp = ptr;
	if (ft_strcmp(h->error, "quoted"))
		ptr = trap_lbeldi(newline_tospace(ptr));
	else
	{
		ptr = trap_lbeldi(ptr);
		ft_strdel(&h->error);
	}
	ft_strdel(&tmp);
	return (ptr);
}

char	*voidyx(int *fd, int *keeper, char *xtr, t_holder *h)
{
	pid_t		sub_pid;
	char		*str;

	sub_pid = fork();
	if (sub_pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		h->line = xtr;
		ft_putchar('\0');
		shell_execute(h, 0);
		cheap_trick(keeper, 1);
		exit(0);
	}
	else
	{
		waitpid(sub_pid, 0, 0);
		str = one_line(h, fd);
	}
	return (str);
}

char	*dollar_parenthesis(t_holder *h, char *str, int *i)
{
	char		*xtr;
	int			keeper[3];
	int			fd[2];

	if (!count_subshell_parenthesis(h->line + *i))
		adjust_line(h, i);
	xtr = subshell_parser(h->line, i);
	cheap_trick(keeper, 0);
	pipe(fd);
	str = ft_strjoin_f(str, voidyx(fd, keeper, xtr, h), 3);
	ft_strdel(&xtr);
	close(fd[0]);
	close(fd[1]);
	cheap_trick(keeper, 1);
	return (str);
}
