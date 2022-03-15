/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 22:37:24 by aariss            #+#    #+#             */
/*   Updated: 2020/01/28 16:56:46 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		is_escape_white(char c)
{
	if (c == 'a' || c == 'b' || c == 'f'
			|| c == 'n' || c == 'r' || c == 't' || c == 'v')
		return (1);
	return (0);
}

void	white_broker(char **str, char **cmd)
{
	(**cmd == 'a') ? *str = ft_joinchar(*str, '\a') : 0;
	(**cmd == 'b') ? *str = ft_joinchar(*str, '\b') : 0;
	(**cmd == 'f') ? *str = ft_joinchar(*str, '\f') : 0;
	(**cmd == 'n') ? *str = ft_joinchar(*str, '\n') : 0;
	(**cmd == 'r') ? *str = ft_joinchar(*str, '\r') : 0;
	(**cmd == 't') ? *str = ft_joinchar(*str, '\t') : 0;
	(**cmd == 'v') ? *str = ft_joinchar(*str, '\v') : 0;
}

char	**echo_replace_white(char **cmd)
{
	char	*tmp;
	char	**head;

	head = cmd;
	while (*cmd)
	{
		if ((count_accurance(*cmd, 39) % 2 == 0
			&& count_accurance(*cmd, 39) != 0)
			|| (count_accurance(*cmd, '"') % 2 == 0
			&& count_accurance(*cmd, '"') != 0))
		{
			tmp = *cmd;
			*cmd = rip_whites(*cmd);
			ft_strdel(&tmp);
		}
		cmd += 1;
	}
	return (head);
}

void	echo_master(char **cmd, int flag)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		ft_putstr(cmd[i]);
		(cmd[i + 1]) ? ft_putchar(' ') : 0;
		i += 1;
	}
	(flag) ? ft_putchar('\n') : 0;
}

int		ft_echo(t_holder *h)
{
	char	**cmd;

	if (fcntl(1, F_GETFD) == -1)
	{
		ft_putendl_fd("42sh: echo: write error: Bad file descriptor", 2);
		return (1);
	}
	cmd = h->lst->cmd;
	if (ft_strcmp(cmd[1], "-e"))
		rip_quotes(cmd);
	if (ft_strcmp(cmd[1], "-n") == 0)
		echo_master(cmd + 2, 0);
	else if (ft_strcmp(cmd[1], "-e") == 0)
	{
		echo_replace_white(cmd + 2);
		rip_quotes(cmd);
		echo_master(cmd + 2, 1);
	}
	else if (ft_strcmp(cmd[1], "-E") == 0)
		echo_master(cmd + 2, 1);
	else
		echo_master(cmd + 1, 1);
	return (0);
}
