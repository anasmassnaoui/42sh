/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_pid_sys_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 10:56:22 by aariss            #+#    #+#             */
/*   Updated: 2020/02/06 23:36:54 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*path_maker(char **tab_cmd, char *arg, int *j)
{
	int		i;
	char	*tmp;
	char	*temp;

	i = -1;
	tmp = ft_strjoin("/", arg);
	while (tab_cmd[++i])
	{
		temp = arg;
		(arg = ft_strjoin(tab_cmd[i], tmp)) ? ft_strdel(&temp) : 0;
		if (access(arg, F_OK) == 0)
		{
			*j = 1;
			break ;
		}
	}
	ft_free2d(tab_cmd);
	ft_strdel(&tmp);
	return (arg);
}

void	sys_cmd(char **command, char *arg, pid_t *get, t_holder *h)
{
	char	**tab_cmd;
	char	*cmd_before;
	int		j;

	j = 0;
	cmd_before = (arg) ? ft_strdup(arg) : NULL;
	if (arg && ft_strncmp(arg, "./", 2) != 0)
	{
		if (!(tab_cmd = get_path(&h->head_ref)))
		{
			h->error = ft_strjoin("command not found: ", arg);
			execute_handler(arg, NULL, NULL, h);
			ft_strdel(&cmd_before);
			ft_strdel(&arg);
			ft_strdel(&h->error);
			return ;
		}
		arg = path_maker(tab_cmd, arg, &j);
	}
	if (j == 1)
		add_in_hash(&h->hash, cmd_before, arg, 1);
	execute(command, arg, get, h);
	ft_strdel(&cmd_before);
}

char	**command_disturb(char **command, char **path, char **path_found)
{
	if ((command[0][0] == '"' && command[0][1] == '"')
			|| (command[0][0] == 39 && command[0][1] == 39))
	{
		ft_strdel(&command[0]);
		command[0] = ft_strdup(" ");
	}
	command = rip_quotes(command);
	*path = NULL;
	*path_found = NULL;
	return (command);
}

void	child_pid(char **command, t_holder *h, pid_t *get, t_bool use_hash)
{
	char	*path;
	char	*path_found;
	char	*path_found2;
	int		index;

	index = 0;
	if (command[0])
		command = command_disturb(command, &path, &path_found);
	path = (command[0]) ? ft_strdup(command[0]) : NULL;
	h->tmp = path;
	index = hash_str(path);
	path_found = NULL;
	if (use_hash && temporaire_variable(-1) == 0)
		path_found = verify_if_exits(path, h->hash.liste[index]);
	if (path_found != NULL && temporaire_variable(-1) == 0)
	{
		path_found2 = ft_strdup(path_found);
		ft_strdel(&path);
		execute(command, path_found2, get, h);
	}
	else if (path && path[0] == '/')
		execute(command, path, get, h);
	else
		sys_cmd(command, path, get, h);
}
