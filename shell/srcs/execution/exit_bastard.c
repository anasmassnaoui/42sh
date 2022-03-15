/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bastard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 22:58:37 by aariss            #+#    #+#             */
/*   Updated: 2020/02/15 18:36:54 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		ft_str_isdigit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str += 1;
	}
	return (1);
}

void	exit_bastard(t_holder *h, int status)
{
	if (status != -666)
		free_structure(h, 1);
	if (status == -1)
		exit(255);
	else if (status == 0)
		exit(0);
	else
		exit(status);
}
