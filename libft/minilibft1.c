/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 11:37:27 by myamani           #+#    #+#             */
/*   Updated: 2020/01/23 11:37:33 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	arg_f(va_list list, t_vari *v)
{
	v->str = va_arg(list, char*);
	v->string = ft_strjoin(v->string, v->str);
	free(v->str);
}

void	arg_c(va_list list, t_vari *v)
{
	v->str_tmp[0] = (char)va_arg(list, int);
	v->str_tmp[1] = '\0';
	v->string = ft_strjoin(v->string, v->str_tmp);
}

void	arg_else(t_vari *v, char *args)
{
	v->str_tmp[0] = args[v->i];
	v->str_tmp[1] = '\0';
	v->string = ft_strjoin(v->string, v->str_tmp);
}
