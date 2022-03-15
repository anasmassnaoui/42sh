/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:46:42 by aariss            #+#    #+#             */
/*   Updated: 2020/02/17 14:15:16 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*kill_one(char *line, char c)
{
	if (ft_strlen(line) && line[ft_strlen(line) - 1] == c)
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

static int	heredoc_ctrld(char **new_line, char **here)
{
	*new_line = readline("heredoc> ");
	if (*new_line[0] == -15)
	{
		ft_strdel(here);
		ft_strdel(new_line);
		*here = ft_strdup("");
		return (0);
	}
	else if (ft_strchr(*new_line, -8))
	{
		*here = ft_strjoin_f(ft_joinchar(ft_strdup(""), -8), *here, 3);
		if (ft_strlen(*new_line) > 1)
		{
			*new_line = kill_one(*new_line, -8);
			if (ft_strlen(*new_line) != 0)
			{
				*here = ft_strjoin_f(*here, *new_line, 1);
				*here = ft_joinchar(*here, '\n');
			}
		}
		ft_strdel(&(*new_line));
		return (0);
	}
	return (1);
}

static void	heredoc_whatever(char *ptr, char *new_line, char **here)
{
	while (ft_strcmp(new_line, ptr) != 0)
	{
		ft_strdel(&new_line);
		if (!heredoc_ctrld(&new_line, here))
			break ;
		if (ft_strchr(new_line, '$'))
			new_line = dollar_doer(new_line,
				get_set_holder(false, NULL)->head_ref);
		new_line = kill_one(new_line, '\n');
		if (!ft_strcmp(new_line, ptr))
		{
			ft_strdel(&new_line);
			break ;
		}
		if (ft_strlen(new_line) != 0)
		{
			*here = ft_strjoin_f(*here, new_line, 1);
			*here = ft_joinchar(*here, '\n');
		}
	}
}

static void	heredoc_parser(char *line, int start, int *i, char **str)
{
	char	*ptr;
	char	*heredoc;
	char	*new_line;

	new_line = NULL;
	ptr = ft_strsub(line, start, *i - start);
	if (ft_strchr(ptr, '$'))
		ptr = dollar_doer(ptr, get_set_holder(false, NULL)->head_ref);
	*str = ft_joinchar(*str, ' ');
	heredoc = ft_strdup("");
	if (ft_strlen(ptr))
	{
		get_set_holder(false, 0)->ctrl_check = true;
		heredoc = ft_joinchar(heredoc, HEREDOC);
		new_line = ft_strdup("");
		heredoc_whatever(ptr, new_line, &heredoc);
		ft_strdel(&ptr);
		heredoc = ft_joinchar(heredoc, HEREDOC);
		*str = ft_strjoin_f(*str, heredoc, 3);
	}
}

void		heredoc(char *line, int start, int *i, char **str)
{
	*str = ft_joinchar(*str, line[*i]);
	(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i) += 1;
	start = *i;
	while (line[*i] && line[*i] != ' '
		&& line[*i] != ';' && !ft_istoken(line[*i])
		&& line[*i] != '|')
		(*i) += 1;
	heredoc_parser(line, start, i, str);
}
