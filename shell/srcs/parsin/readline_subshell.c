/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_subshell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:13:45 by aariss            #+#    #+#             */
/*   Updated: 2020/01/12 18:13:48 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		quote_skipper(char *line, int i)
{
	int	keeper;

	keeper = line[i];
	i += 1;
	while (line[i] && line[i] != keeper)
		i += 1;
	return (i);
}

int		count_subshell_parenthesis(char *line)
{
	int		i;
	int		count;
	int		monkey;

	i = -1;
	count = 0;
	monkey = 0;
	while (line[++i])
	{
		if (line[i] == '$' && line[i + 1] == '(')
		{
			monkey += 1;
			i += 1;
		}
		else if (line[i] == ')')
		{
			monkey -= 1;
			count += 1;
		}
		else if (ft_isquote(line[i]))
			i = quote_skipper(line, i);
	}
	if (monkey == 0)
		return (count);
	return (0);
}

void	take_decision(t_holder *h, char **new_line, char *subshell)
{
	if (*new_line && *new_line[0] != -15)
		h->line = ft_strjoin_f(h->line, subshell, 3);
	else
	{
		h->error = ft_strdup("ctrl_c");
		ft_strdel(new_line);
	}
}

void	adjust_line(t_holder *h, int *i)
{
	char	*new_line;
	char	*subshell;
	char	*tata;

	subshell = ft_strdup("");
	get_set_holder(false, 0)->ctrl_check = true;
	while ((tata = ft_strjoin(h->line, subshell))
		&& !count_subshell_parenthesis(tata + *i))
	{
		ft_strdel(&tata);
		new_line = readline("cmdsubst> ");
		if (new_line[0] == -15)
		{
			ft_strdel(&subshell);
			break ;
		}
		subshell = ft_strjoin_f(subshell, new_line, 3);
	}
	(tata) ? ft_strdel(&tata) : 0;
	take_decision(h, &new_line, subshell);
}
