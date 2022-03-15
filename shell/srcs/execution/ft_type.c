/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 13:03:59 by myamani           #+#    #+#             */
/*   Updated: 2020/02/14 11:14:32 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_hash_cmd	*get_hash(char *cmd, t_holder *h)
{
	int			i;
	t_hash_cmd	*tmp;

	i = 0;
	while (i < h->hash.size)
	{
		tmp = h->hash.liste[i];
		while (tmp)
		{
			if (!ft_strcmp(tmp->cmd, cmd))
				return (tmp);
			tmp = tmp->next;
		}
		i++;
	}
	return (NULL);
}

char		*get_cmd1(t_varss *v)
{
	if (v->env->value)
		v->tableau = ft_strsplit(v->env->value, ':');
	while (v->tableau[v->i])
	{
		v->cmd2 = ft_strjoin(v->tableau[v->i], v->cmd1);
		if (access(v->cmd2, X_OK) == 0)
		{
			ft_strdel((void *)&v->cmd1);
			(v->env->value) ? ft_free2d(v->tableau) : 0;
			return (v->cmd2);
		}
		ft_strdel((void *)&v->cmd2);
		v->i++;
	}
	(v->env->value) ? ft_free2d(v->tableau) : 0;
	return (NULL);
}

char		*get_cmd(t_holder *h, char *cmd)
{
	t_varss v;

	v.i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	v.cmd1 = ft_strjoin("/", cmd);
	v.env = h->head_ref;
	v.tableau = NULL;
	v.cmd2 = NULL;
	while (v.env)
	{
		if (!ft_strcmp("PATH", v.env->var))
			if (get_cmd1(&v))
				return (v.cmd2);
		v.env = v.env->next;
	}
	ft_strdel((void *)&v.cmd1);
	ft_strdel((void *)&v.cmd2);
	return (NULL);
}

t_alias		*get_alias(t_alias *alias, char *cmd)
{
	while (alias)
	{
		if (!ft_strcmp(alias->alias, cmd))
			return (alias);
		alias = alias->next;
	}
	return (NULL);
}

void		ft_type(t_holder *h, char **cmd)
{
	char		*path;
	t_alias		*alias;
	int			i;
	t_hash_cmd	*tmp;

	i = 0;
	alias = h->aliases;
	while (cmd[++i])
	{
		if ((alias = get_alias(h->aliases, cmd[i])))
			ft_dprintf(1, "%s is aliased to `%s`\n",
			alias->alias, alias->original);
		else if (own_commands(cmd + i))
			ft_dprintf(1, "%s is a shell builtin\n", cmd[i]);
		else if ((tmp = get_hash(cmd[i], h)))
			ft_dprintf(1, "%s is hashed (%s)\n", cmd[i], tmp->path);
		else if ((path = get_cmd(h, cmd[i])))
		{
			ft_dprintf(1, "%s is %s\n", cmd[i], path);
			ft_strdel((void *)&path);
		}
		else if ((get_set_holder(false, NULL)->last_status = 1))
			ft_dprintf(1, "42sh: type: %s: not found\n", cmd[i]);
	}
}
