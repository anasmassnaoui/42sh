/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_extras.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:01:22 by aariss            #+#    #+#             */
/*   Updated: 2020/02/12 13:31:19 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	skip_alpha(char *line, int *i)
{
	(*i)++;
	while (ft_isalpha(line[*i]) && line[*i])
		(*i)++;
	(*i)--;
}

int		skip_quotes(char *str)
{
	char	q;
	int		i;

	i = 0;
	q = str[i];
	i++;
	while (str[i] && str[i] != q)
		i++;
	i++;
	return (i);
}

int		is_toset(char *str)
{
	int i;

	i = 0;
	if (!ft_isdigit(str[i]) && str[0] != '=')
		while (str[i] != '\0')
		{
			if (i > 0 && str[i] == '=')
				return (1);
			if (ft_isalnum(str[i]) == 0 && str[i] != '_')
				return (0);
			i++;
		}
	return (0);
}

int		retrieve_the_digit(char *name, int delimiter)
{
	if (delimiter == 0)
		return (ft_atoi(name));
	while (ft_isdigit(*name))
		name++;
	while (ft_istoken(*name))
		name++;
	return (ft_atoi(name));
}

int		count_arg(char **kratos)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (kratos[i])
	{
		if (!ultimate_check(kratos[i]))
			count++;
		i++;
	}
	return (count + 1);
}
