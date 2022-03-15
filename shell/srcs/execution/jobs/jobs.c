/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 13:57:01 by aariss            #+#    #+#             */
/*   Updated: 2020/01/27 18:40:28 by amassnao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/shell.h"

int		check_flag(char **args, char *head, char *message, t_bool use_flag)
{
	int	flag;
	int	j;

	flag = 0;
	while (*(++args) && (j = -1))
		if ((*args)[++j] == '-')
			while ((*args)[++j])
			{
				if ((*args)[j] == 'l' && use_flag)
					flag = 1;
				else if ((*args)[j] == 'p' && use_flag)
					flag = 2;
				else
				{
					ft_putstr_fd(head, 2);
					ft_putchar_fd((*args)[j], 2);
					ft_putendl_fd(": invalid option", 2);
					ft_putendl_fd(message, 2);
					return (-1);
				}
			}
		else
			break ;
	return (flag);
}

int		show_jobs_msg(char *cmd, char *flag)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(flag, 2);
	ft_putendl_fd(": no such job", 2);
	return (1);
}

int		show_jobs(t_holder *h, char **args, int flag, int status)
{
	if (!*args)
		return (status);
	if (!ft_strncmp(*args, "%%", 2))
	{
		if (!h->groups || (h->groups
					&& !show_groups(h->groups, h->groups->id, flag)))
			status = show_jobs_msg("jobs", *args);
	}
	else if (!valid_id(*args))
		status = show_jobs_msg("jobs", *args);
	else if (valid_id(*args) && !show_groups(h->groups, valid_id(*args), flag))
		status = show_jobs_msg("jobs", *args);
	return (show_jobs(h, args + 1, flag, status));
}

int		jobs(t_holder *h, char **args)
{
	int		status;
	int		i;
	int		flag;

	status = 0;
	i = 0;
	if ((flag = check_flag(args, "jobs: -",
	"jobs: usage: jobs [-lp] [jobspec ...]", true)) < 0)
		return (1);
	while (args[++i])
		if (!ft_strncmp(args[i], "-", 1))
			continue;
		else
			break ;
	if (args[i])
		status = show_jobs(h, args + i, flag, 0);
	else
		show_groups(h->groups, 0, flag);
	return (status);
}
