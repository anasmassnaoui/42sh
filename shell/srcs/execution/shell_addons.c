/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_addons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 19:32:23 by aariss            #+#    #+#             */
/*   Updated: 2020/02/13 19:32:29 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	verify_error(char *termtype, int s)
{
	if (termtype == NULL)
	{
		ft_putstr_fd("Could not access the TERM ", 2);
		ft_putstr_fd("variable in the environment\n", 2);
		exit(0);
	}
	if (s < 0)
	{
		ft_putstr_fd("Could not access the termcap data base.\n", 2);
		exit(0);
	}
	if (s == 0)
	{
		ft_putstr_fd("Terminal type ", 2);
		ft_putstr_fd(termtype, 2);
		ft_putstr_fd("is not defined.\n", 2);
		exit(0);
	}
}

t_bool	is_complete(char *str)
{
	int	keeper;

	keeper = 0;
	while (*str)
	{
		if (ft_isquote(*str))
		{
			keeper = *str;
			str += 1;
			while (*str && *str != keeper)
			{
				if (*str == -7)
					str += 2;
				str += 1;
			}
			if (*str != keeper)
				return (false);
		}
		str += 1;
	}
	return (true);
}

t_bool	cmd_list_check(t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		while (lst->cmd[i])
		{
			if (!is_complete(lst->cmd[i]))
				return (false);
			i += 1;
		}
		i = 0;
		lst = lst->next;
	}
	return (true);
}
