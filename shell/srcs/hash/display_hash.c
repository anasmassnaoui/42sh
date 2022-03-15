/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 00:23:12 by aariss            #+#    #+#             */
/*   Updated: 2020/01/28 18:37:39 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

int		get_lenght(int size)
{
	int	i;

	i = 0;
	if (size == 0)
		i++;
	while (size > 0)
	{
		size = size / 10;
		i++;
	}
	return (i);
}

void	display_space(int max, int nbr)
{
	int	i;

	i = 0;
	while (i < (max - nbr))
	{
		ft_putstr(" ");
		i++;
	}
}

void	display_hash(t_hash hash)
{
	int	i;

	i = 0;
	if (hash.count == 0)
		ft_putendl_fd("hash: hash table empty", 1);
	else
		ft_putendl_fd("hits	command ", 1);
	while (i < hash.size)
	{
		while (hash.liste[i])
		{
			display_space(4, get_lenght(hash.liste[i]->count));
			ft_putnbr_fd(hash.liste[i]->count, 1);
			ft_putstr_fd("	", 1);
			ft_putendl_fd(hash.liste[i]->path, 1);
			hash.liste[i] = hash.liste[i]->next;
		}
		i++;
	}
}

char	*verify_if_exits(char *cmd, t_hash_cmd *hash)
{
	t_hash_cmd	*tmp_head;

	tmp_head = hash;
	while (tmp_head)
	{
		if (ft_strcmp(cmd, tmp_head->cmd) == 0)
		{
			tmp_head->count++;
			return (tmp_head->path);
		}
		tmp_head = tmp_head->next;
	}
	return (NULL);
}

int		hash_error_msg(char *flag)
{
	ft_putstr_fd("42sh: hash: ", 2);
	ft_putstr_fd(flag, 2);
	ft_putendl_fd(": not found", 2);
	return (1);
}
