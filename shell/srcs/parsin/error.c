/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 16:50:36 by aariss            #+#    #+#             */
/*   Updated: 2020/01/12 16:50:41 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	error_monkey(t_cmd **lst)
{
	if (!(*lst)->cmd[0])
		get_set_holder(false, NULL)->error = ft_strdup("parse_error");
}