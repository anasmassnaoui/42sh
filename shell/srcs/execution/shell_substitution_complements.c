/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_substitution_complements.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:13:04 by aariss            #+#    #+#             */
/*   Updated: 2020/01/21 17:13:28 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*newline_tospace(char *line)
{
	char	*head;

	head = line;
	while (*line)
	{
		if (*line == '\n')
			*line = ' ';
		line += 1;
	}
	return (head);
}

char	*kill_newline(char *line)
{
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

char	*trap_lbeldi(char *str)
{
	int		i;
	char	*ptr;

	i = 0;
	str = kill_newline(str);
	ptr = ft_strnew(1);
	while (str[i])
	{
		if (str[i] == ' ')
		{
			ptr = ft_joinchar(ptr, ' ');
			while (str[i] && str[i] == ' ')
				i += 1;
			i -= 1;
		}
		else
			ptr = ft_joinchar(ptr, str[i]);
		i += 1;
	}
	return (ptr);
}
