/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_addons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 12:55:50 by aariss            #+#    #+#             */
/*   Updated: 2020/02/17 15:43:09 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*expansion_parser(char *line, int *i)
{
	char	*str;
	int		x;

	x = 0;
	str = ft_strdup("");
	str = ft_joinchar(str, line[(*i)++]);
	str = ft_joinchar(str, line[(*i)++]);
	while (line[*i])
	{
		if (line[*i] == '}' && !x)
			break ;
		else if (line[*i] == '$' && line[*i + 1] == '{')
			x += 1;
		else if (line[*i] == '}')
			x -= 1;
		else if (ft_isquote(line[*i]))
		{
			str = look_elsewhere(line, i, str);
			(*i) += 1;
		}
		str = ft_joinchar(str, line[*i]);
		(*i) += 1;
	}
	str = ft_joinchar(str, line[(*i)]);
	return (str);
}

char	*dollar_curly(char *cmd, char *str, int *i, t_env *env)
{
	char	*ptr;
	char	*exp;

	ptr = expansion_parser(cmd, i);
	exp = parameter_expansion(ptr, env);
	str = (exp) ? ft_strjoin_f(str, exp, 1) : ft_strjoin_f(str, "", 1);
	ft_strdel(&exp);
	return (str);
}

char	*dollar_quote_related(char *cmd, char *str, int *i, t_quote sp)
{
	sp.keeper = cmd[*i];
	str = ft_joinchar(str, cmd[*i]);
	(*i) += 1;
	while (cmd[*i] && cmd[*i] != sp.keeper)
	{
		if (cmd[*i] == '$')
			str = dollar_handle_quoted(str, cmd, i, sp);
		else if (cmd[*i] == -7)
		{
			str = ft_joinchar(str, -7);
			str = ft_joinchar(str, sp.keeper);
			str = ft_joinchar(str, -7);
			(*i) += 2;
		}
		else
			str = ft_joinchar(str, cmd[*i]);
		(*i) += 1;
	}
	str = ft_joinchar(str, sp.keeper);
	return (str);
}

char	*dollar_master(char *cmd, char *str, int *i, t_env *env)
{
	char *exit_status;

	exit_status = ft_itoa(get_set_holder(false, NULL)->last_status);
	if (cmd[(*i) + 1] == '\0' || cmd[*i] == ' ')
		str = ft_joinchar(str, '$');
	else if (cmd[(*i) + 1] == '?')
	{
		str = ft_strjoin_f(str, exit_status, 1);
		(*i) += 1;
	}
	else if (cmd[*i + 1] == '{')
		str = dollar_curly(cmd, str, i, env);
	else
		str = dollar_handle_simple(str, cmd, i, env);
	ft_strdel(&exit_status);
	return (str);
}

char	*dollar_doer(char *cmd, t_env *env)
{
	int		i;
	char	*str;
	t_quote	sp;

	i = -1;
	str = ft_strdup("");
	sp.env = env;
	while (cmd[++i])
	{
		if (ft_isquote(cmd[i]) && ft_strchr(cmd + i, '$'))
			str = dollar_quote_related(cmd, str, &i, sp);
		else if (cmd[i] == '$')
			str = dollar_master(cmd, str, &i, env);
		else
			str = ft_joinchar(str, cmd[i]);
		if (!cmd[i])
		{
			str = ft_joinchar(str, '\0');
			break ;
		}
	}
	ft_strdel(&cmd);
	return (str);
}
