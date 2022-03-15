/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:50:38 by aariss            #+#    #+#             */
/*   Updated: 2020/02/14 18:07:50 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			builtin_cmd_2(t_holder *h, int j, int i)
{
	int		status;

	status = 0;
	if (j == 1)
		status = ft_echo(h);
	else if (j == 9)
		ft_set(h);
	else if (j == 8)
		return (ft_export(h->lst->cmd, h));
	else if (j == 3 || j == 10)
		alias_manager(h);
	else if (j == 11)
		status = hash_manager(h, i);
	else if (j == 2)
	{
		if (!(ft_cd(h)))
			return (1);
	}
	else
		status = which_and_del(h, j);
	return (status);
}

int			builtin_cmds_1(t_holder *h, int j, int i)
{
	int	status;

	status = 0;
	if ((ft_strcmp(h->lst->cmd[0], "hash") == 0) && !h->lst->cmd[1])
		display_hash(h->hash);
	else
		status = builtin_cmd_2(h, j, i);
	return (status);
}

int			build_status(int status)
{
	if (fork() == 0)
		exit(status);
	wait(&status);
	return (status);
}

int			builtin_cmds(t_holder *h, int j, t_bool exit_after)
{
	int		status;
	int		x;

	status = 0;
	x = 0;
	if (!exit_after && !deathly_hallows(h->lst->red))
		return (1);
	if (j == 5)
		status = (jobs(h, h->lst->cmd));
	else if (j == 13)
		status = (fg(h, h->lst->cmd));
	else if (j == 14)
		status = (bg(h, h->lst->cmd));
	else if (j == 12)
		ft_type(h, h->lst->cmd);
	else if (j == 7 && (exit_after = true))
		status = ft_exit(h, &x);
	else if (j == 15)
		status = fc_manager(h, status);
	else
		status = builtin_cmds_1(h, j, 1);
	if (exit_after && !x)
		exit(status);
	return (build_status(status));
}

int			own_commands(char **cmds)
{
	char	*command[17];

	command[1] = "echo";
	command[2] = "cd";
	command[3] = "alias";
	command[4] = "unset";
	command[5] = "jobs";
	command[6] = "which";
	command[7] = "exit";
	command[8] = "export";
	command[9] = "set";
	command[10] = "unalias";
	command[11] = "hash";
	command[12] = "type";
	command[13] = "fg";
	command[14] = "bg";
	command[15] = "fc";
	command[16] = NULL;
	MAD_DECLARE(int, i, 1);
	while (command[i])
	{
		if ((ft_strcmp(cmds[0], command[i++]) == 0))
			return (--i);
	}
	return (0);
}
