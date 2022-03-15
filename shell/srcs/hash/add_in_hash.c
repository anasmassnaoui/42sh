/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_in_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 00:15:48 by aariss            #+#    #+#             */
/*   Updated: 2020/02/13 17:29:00 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

int			get_pow(int p, int i)
{
	int result;

	result = 1;
	while (i > 0)
	{
		result = result * (p * i);
		i--;
	}
	return (result % SIZE_HASH);
}

int			hash_str(char *cmd)
{
	int				i;
	int				p;
	unsigned int	count;
	int				len;

	i = 0;
	p = 31;
	count = 0;
	len = ft_strlen(cmd);
	while (i < len)
	{
		count += (cmd[i] - 'a' + 1) * (get_pow(p, i));
		i++;
	}
	return (count % SIZE_HASH);
}

t_hash_cmd	*get_one_hash(char *cmd, char *full_cmd, int i)
{
	t_hash_cmd *hash;

	hash = (t_hash_cmd *)malloc(sizeof(t_hash_cmd));
	hash->cmd = ft_strdup(cmd);
	hash->path = ft_strdup(full_cmd);
	hash->count = i;
	hash->next = NULL;
	return (hash);
}

void		add_in_hash(t_hash *hash, char *cmd, char *full_cmd, int i)
{
	int			index;
	t_hash_cmd	*hash_cmd;

	index = hash_str(cmd);
	if (!hash->liste[index])
	{
		hash->liste[index] = get_one_hash(cmd, full_cmd, i);
		hash->count++;
	}
	else
	{
		hash_cmd = hash->liste[index];
		if (ft_strcmp(hash->liste[index]->cmd, cmd) == 0)
			return ;
		while (hash_cmd->next)
		{
			if (ft_strcmp(hash->liste[index]->cmd, cmd) == 0)
				return ;
			hash_cmd = hash_cmd->next;
		}
		hash_cmd->next = get_one_hash(cmd, full_cmd, i);
	}
}

int			compare_builtin(char *cmd)
{
	char	*tmp[15];
	int		i;

	i = -1;
	tmp[0] = "echo";
	tmp[1] = "cd";
	tmp[2] = "alias";
	tmp[3] = "unset";
	tmp[4] = "jobs";
	tmp[5] = "which";
	tmp[6] = "exit";
	tmp[7] = "export";
	tmp[8] = "set";
	tmp[9] = "unalias";
	tmp[10] = "hash";
	tmp[11] = "type";
	tmp[12] = "fg";
	tmp[13] = "bg";
	tmp[14] = "fc";
	while (++i < 15)
	{
		if (ft_strcmp(cmd, tmp[i]) == 0)
			return (-1);
	}
	return (0);
}
