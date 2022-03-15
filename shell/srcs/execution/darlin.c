/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:50:13 by aariss            #+#    #+#             */
/*   Updated: 2020/02/07 17:35:23 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		pipe_master(t_cmd *lst, int *keeper, int *backup_zero, int is_tmp)
{
	int			fds[2];

	get_set_holder(false, 0)->fd_0 = -1;
	get_set_holder(false, 0)->fd_1 = -1;
	dup2(*backup_zero, 0);
	close(*backup_zero);
	if (lst->next)
	{
		pipe(fds);
		is_tmp = 1;
		*backup_zero = fds[0];
		get_set_holder(false, 0)->fd_0 = fds[0];
		get_set_holder(false, 0)->fd_1 = fds[1];
		dup2(fds[1], 1);
		close(fds[1]);
	}
	else
	{
		dup2(keeper[1], 1);
		dup2(keeper[2], 2);
	}
	return (is_tmp);
}

void	cheap_trick(int *keeper, int trick)
{
	if (trick == 0)
	{
		keeper[0] = dup2(0, 101);
		keeper[1] = dup2(1, 102);
		keeper[2] = dup2(2, 103);
	}
	if (trick == 1)
	{
		dup2(keeper[0], 0);
		dup2(keeper[1], 1);
		dup2(keeper[2], 2);
		close(keeper[0]);
		close(keeper[1]);
		close(keeper[2]);
	}
}

void	command_execution(t_holder *h, t_tmp_env *x, t_cmd *lst, pid_t *get)
{
	t_bool use_hash;

	use_hash = true;
	env_val_copy(h->head_ref);
	if (lst->cmd && lst->cmd[0] && is_a_builtin(lst->cmd[0]))
	{
		add_env_tmp(&h->head_ref, h->tmp_env, 3, true);
		h->tmp_env = NULL;
		if (!h->pipe_exist && !h->background)
			x->command_status = builtin_cmds(h, own_commands(lst->cmd), false);
		else
			execute_handler(lst->cmd[0], NULL, NULL, h);
	}
	else if (lst->cmd)
	{
		if (h->tmp_env)
			use_hash = false;
		add_env_tmp(&h->head_ref, h->tmp_env, lst->cmd[0] ? 3 : 0
		, lst->cmd[0] ? true : false);
		child_pid(lst->cmd, h, get, use_hash);
		h->tmp_env = NULL;
	}
	env_diff(&h->head_ref, NULL, h->head_ref);
}

int		master_of_death(t_holder *h, int *keeper)
{
	int			backup_zero;
	t_cmd		*lst;
	pid_t		get;
	t_tmp_env	x;

	backup_zero = dup(0);
	lst = h->lst;
	h->pipe_exist = false;
	x.command_status = -1;
	while (lst)
	{
		h->lst = lst;
		(lst->next) ? h->pipe_exist = true : 0;
		to_reset_hash(0);
		temporaire_variable(0);
		extract_env(h);
		pipe_master(lst, keeper, &backup_zero, x.is_tmp);
		command_execution(h, &x, lst, &get);
		hash_env_rest_treat(h, &x);
		(h->error) ? ft_strdel(&h->error) : 0;
		lst = lst->next;
		h->tmp_env = NULL;
	}
	x.command_status = kill_pid(h, keeper, x.command_status);
	return (x.command_status);
}

int		darlin_g(t_holder *h)
{
	int			keeper[3];

	cheap_trick(keeper, 0);
	return (master_of_death(h, keeper));
}
