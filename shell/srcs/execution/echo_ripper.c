/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_ripper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 22:44:56 by aariss            #+#    #+#             */
/*   Updated: 2020/01/12 22:44:57 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		count_ca(char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
		{
			MAD_DECLARE(int, keeper, str[i]);
			while (str[i] && str[i] != keeper)
			{
				if (str[i] == -7)
					i += 2;
				i += 1;
			}
			if (str[i] == keeper && str[i] == c)
				count++;
		}
		i++;
	}
	return (count);
}

char	**rip_quotes(char **cmd)
{
	char	*tmp;
	char	**head;

	tmp = NULL;
	head = cmd;
	while (*cmd)
	{
		if (count_ca(*cmd, 39) != 0 || count_ca(*cmd, '"') != 0)
		{
			tmp = *cmd;
			*cmd = ignore_quote(*cmd, 1);
			ft_strdel(&tmp);
		}
		cmd += 1;
	}
	return (head);
}

char	*rip_whites(char *cmd)
{
	char	*str;

	if (!(str = (char*)malloc(sizeof(char) * ft_strlen(cmd) + 1)))
		return (NULL);
	while (*cmd)
	{
		if (*cmd == 92)
		{
			cmd += 1;
			if (is_escape_white(*cmd))
				white_broker(&str, &cmd);
			else
			{
				str = ft_joinchar(str, 92);
				str = ft_joinchar(str, *cmd);
			}
		}
		else
			str = ft_joinchar(str, *cmd);
		cmd += 1;
	}
	return (str);
}
