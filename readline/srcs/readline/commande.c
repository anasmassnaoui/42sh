/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:57:29 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/02/15 17:20:53 by hbenlarh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "auto.h"

void		print_prompt(char *prompt)
{
	ft_putstr(COLOR2);
	ft_putstr(prompt);
	ft_putstr(RESET2);
}

static char	*from_str_to_cmd_two(t_line *line)
{
	char	*newcmd;
	int		len;
	int		t;
	int		i;

	len = ft_strlen((*line).cmd) + ft_strlen((*line).str);
	t = -1;
	i = ft_strlen((*line).cmd);
	newcmd = malloc(sizeof(char) * len + 1);
	while (++t < i)
		newcmd[t] = (*line).cmd[t];
	t = -1;
	while (i < len)
	{
		newcmd[i] = (*line).str[++t];
		i++;
	}
	newcmd[i] = '\0';
	return (newcmd);
}

void		from_str_to_cmd(t_line *line, t_all_hist *history)
{
	char	*newcmd;

	(void)history;
	newcmd = from_str_to_cmd_two(line);
	ft_strdel(&((*line).cmd));
	(*line).cmd = newcmd;
	if (get_escape(line) == -1)
		(*line).cmd[ft_strlen((*line).cmd) - 2] = '\0';
	(*line).curs = 0;
}
