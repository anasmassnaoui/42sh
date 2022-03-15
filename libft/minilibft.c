/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 20:39:56 by myamani           #+#    #+#             */
/*   Updated: 2020/01/23 11:36:47 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_args(char *args, va_list list)
{
	t_vari v;

	v.i = 0;
	v.string = ft_strnew(1);
	while (args[v.i])
	{
		v.tmp = v.string;
		if (ft_strnequ(args + v.i, "%f", 2) ? ++v.i : 1 != 1)
			arg_f(list, &v);
		else if (ft_strnequ(args + v.i, "%s", 2) ? ++v.i : 1 != 1)
			v.string = ft_strjoin(v.string, va_arg(list, char*));
		else if (ft_strnequ(args + v.i, "%d", 2) ? ++v.i : 1 != 1)
			v.string = ft_strjoin(v.string, ft_itoa(va_arg(list, int)));
		else if (ft_strnequ(args + v.i, "%c", 2) ? ++v.i : 1 != 1)
			arg_c(list, &v);
		else
			arg_else(&v, args);
		free(v.tmp);
		v.i++;
	}
	return (v.string);
}

void	ft_vprintf(int fd, char *format, va_list *lst)
{
	char	*str;

	str = ft_get_args(format, *lst);
	ft_putstr_fd(str, fd);
	ft_strdel((void *)&str);
}

void	ft_printf(char *format, ...)
{
	va_list list;

	va_start(list, format);
	ft_vprintf(1, format, &list);
	va_end(list);
}

void	ft_dprintf(int fd, char *format, ...)
{
	va_list list;

	va_start(list, format);
	ft_vprintf(fd, format, &list);
	va_end(list);
}

char	*ft_join(char *format, ...)
{
	char	*str;
	va_list list;

	va_start(list, format);
	str = ft_get_args(format, list);
	va_end(list);
	return (str);
}
