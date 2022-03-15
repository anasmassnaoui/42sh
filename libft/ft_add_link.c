/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 09:02:53 by aariss            #+#    #+#             */
/*   Updated: 2018/10/16 10:03:23 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_add_link(t_list *list, char *str, size_t size)
{
	t_list *toto;

	toto = (t_list*)malloc(sizeof(t_list));
	if (toto)
	{
		toto->content = str;
		toto->content_size = size;
		toto->next = list;
	}
	return (toto);
}
