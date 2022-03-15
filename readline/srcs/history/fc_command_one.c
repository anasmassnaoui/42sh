/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_command_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:06:07 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/15 13:55:12 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

char	*fc_s_one(t_history *tmp, char **ptr)
{
	if (ptr[2] == NULL)
	{
		ft_putendl_fd(last_node(tmp), 2);
		return (ft_strdup(last_node(tmp)));
	}
	else if (ptr[2][0] == '=')
		return (ft_strdup(ptr[2]));
	else if (ptr[2][ft_strlen(ptr[2]) - 1] == '=')
		return (ft_strdup(ptr[2]));
	else if (ft_strchr(ptr[2], '='))
		return (search_replace(ptr, tmp));
	else
		return (search_in_hist(tmp, ptr[2], ft_atoi(ptr[2])));
}

void	fc_ln_one(t_history *tmp, int t, char **ptr, t_history *cmd)
{
	if (!ft_strcmp(ptr[1], "-l"))
		t = 1;
	else
		t = 0;
	if (ptr[2] == NULL)
		print_history(tmp, t);
	else if (ptr[3] == NULL)
		one_arg_ln(tmp, t, ptr, cmd);
	else
		many_args_ln(tmp, t, ptr, cmd);
}
