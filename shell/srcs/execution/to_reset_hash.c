/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_reset_hash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 21:53:40 by myamani           #+#    #+#             */
/*   Updated: 2020/01/21 21:53:42 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		to_reset_hash(int i)
{
	static int reset_hash;

	if (i == 0)
		reset_hash = 0;
	else if (i == 1)
		reset_hash = 1;
	return (reset_hash);
}
