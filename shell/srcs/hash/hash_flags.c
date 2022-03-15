/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 00:38:29 by aariss            #+#    #+#             */
/*   Updated: 2020/02/13 17:29:11 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

void		clear_hash(t_hash *hash)
{
	int			i;
	t_hash_cmd	*todel;

	i = 0;
	while (i < hash->size)
	{
		while (hash->liste[i])
		{
			ft_strdel(&hash->liste[i]->cmd);
			hash->liste[i]->count = 0;
			ft_strdel(&hash->liste[i]->path);
			todel = hash->liste[i];
			hash->liste[i] = hash->liste[i]->next;
			free(todel);
		}
		i++;
	}
	hash->count = 0;
}

void		hash_flags_three(char *str, char *next_flag)
{
	if (str)
	{
		ft_putendl_fd(str, 1);
		ft_strdel(&str);
	}
	else
		hash_error_msg(next_flag);
}

static char	*hash_flags_four(t_hash_cmd *tmp, char *next)
{
	char	*str;

	str = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->cmd, next) == 0)
			str = ft_strdup(tmp->path);
		tmp = tmp->next;
	}
	return (str);
}

static	int	hash_flags_bis(t_hash *hash, char *flag, char *next)
{
	char		*str;
	int			index;
	t_hash_cmd	*tmp;

	if (ft_strcmp(flag, "-r") == 0)
	{
		clear_hash(hash);
		return (0);
	}
	else if (ft_strcmp(flag, "-t") == 0)
	{
		if (next)
		{
			index = hash_str(next);
			tmp = hash->liste[index];
			str = hash_flags_four(tmp, next);
			hash_flags_three(str, next);
		}
		else
			ft_putendl_fd("42sh: hash: -t: option requires an argument", 2);
		return (0);
	}
	return (-1);
}

int			hash_flags(t_hash *hash, char *flag, char *next_flag, char *cmd)
{
	int i;

	i = 0;
	if (cmd != NULL)
	{
		if (compare_builtin(flag) == -1)
		{
			ft_putstr_fd("42sh: hash: ", 2);
			ft_putstr_fd(flag, 2);
			ft_putendl_fd(" is a builtin", 2);
			ft_strdel(&cmd);
			return (1);
		}
		add_in_hash(hash, flag, cmd, 0);
		ft_strdel(&cmd);
		return (0);
	}
	if (hash_flags_bis(hash, flag, next_flag) == 0)
		return (0);
	else
		i = hash_error_msg(flag);
	return (i);
}
