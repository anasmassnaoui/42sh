/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_temporaire_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 14:35:46 by aariss            #+#    #+#             */
/*   Updated: 2020/02/07 16:33:57 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		hash_env_rest_treat(t_holder *h, t_tmp_env *x)
{
	(void)x;
	if (to_reset_hash(-1) == 1 && temporaire_variable(-1) == 0)
		clear_hash(&h->hash);
	return (1);
}
