/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 22:50:46 by aariss            #+#    #+#             */
/*   Updated: 2020/02/14 23:24:32 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

long long int	ft_atoi_lli(const char *str)
{
	long long int	res;
	int				sign;
	int				i;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + str[i++] - 48;
	}
	return (res * sign);
}

void			error_exit(t_holder *h, int decider)
{
	char	**cmd;
	char	*alpha_required;
	char	*errno;

	cmd = h->lst->cmd;
	alpha_required = NULL;
	errno = NULL;
	if (decider)
	{
		errno = ft_strdup("42sh: number truncated after 18 digits: ");
		alpha_required = ft_strjoin_f(errno, cmd[1], 1);
		ft_putendl_fd(alpha_required, 2);
		ft_strdel(&alpha_required);
		exit_bastard(h, -1);
	}
	errno = ft_strjoin("42sh: exit: ", cmd[1]);
	alpha_required = ft_strjoin_f(errno, ": numeric argument required", 1);
	ft_putendl_fd(alpha_required, 2);
	ft_strdel(&alpha_required);
	exit_bastard(h, -1);
}

void			exit_number(t_holder *h, char **cmd, int atoi_cmd)
{
	char	*lli_str;
	char	*cmd_head;
	char	*head_lli;

	head_lli = NULL;
	if (ft_strlen(cmd[1]) < 19)
		exit_bastard(h, atoi_cmd);
	else if (ft_strlen(cmd[1]) == 19)
	{
		lli_str = ft_strdup("9223372036854775807");
		head_lli = lli_str;
		cmd_head = cmd[1];
		while (*lli_str && *cmd_head && (*lli_str - '0') >= (*cmd_head - '0'))
		{
			lli_str += 1;
			cmd_head += 1;
		}
		ft_strdel(&head_lli);
		if (*cmd_head == '\0')
			exit_bastard(h, atoi_cmd);
		else
			error_exit(h, 1);
	}
	else
		error_exit(h, 1);
}

void			exit_manager(t_holder *h, int atoi_cmd)
{
	char	**cmd;

	cmd = h->lst->cmd;
	if (ft_str_isdigit(cmd[1]) || (cmd[1][0] == '-'
				&& ft_str_isdigit(cmd[1] + 1)))
		exit_number(h, cmd, atoi_cmd);
	else
		error_exit(h, 0);
}

int				ft_exit(t_holder *h, int *x)
{
	char	**cmd;
	int		cmd_len;
	int		atoi_cmd;

	cmd = h->lst->cmd;
	(cmd[1]) ? atoi_cmd = ft_atoi_lli(cmd[1]) : 0;
	cmd_len = count_tab(cmd);
	if (h->groups && !h->force_exit)
	{
		ft_putendl_fd("There are stopped jobs.", 2);
		h->force_exit = true;
		*x = 1;
	}
	else if (cmd_len == 1)
		exit_bastard(h, 0);
	else if (cmd_len == 2)
		exit_manager(h, atoi_cmd);
	else
	{
		ft_putendl_fd("exit: too many arguments", 2);
		*x = 1;
		return (1);
	}
	return (0);
}
