/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 20:27:06 by aariss            #+#    #+#             */
/*   Updated: 2020/02/16 15:22:45 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** search through PATH values for binary if exist or not;
*/

char	*binary_path(char **tableau, char *arg)
{
	int		i;
	char	*tmp;
	char	*s;

	i = 0;
	tmp = ft_strjoin("/", arg);
	while (tableau[i])
	{
		s = ft_strjoin(tableau[i], tmp);
		if (access(s, F_OK) == 0)
		{
			ft_strdel(&tmp);
			return (s);
		}
		ft_strdel(&s);
		i++;
	}
	ft_strdel(&tmp);
	return (NULL);
}

/*
** search for binary path;
*/

void	which_cmd(char *arg, t_env **head_ref)
{
	char	**tableau;
	char	*ret;

	if (!(tableau = get_path(head_ref)))
		return ;
	if ((ret = binary_path(tableau, arg)))
		ft_putendl_fd(ret, 1);
	else
	{
		ret = ft_strjoin(arg, " not found");
		ft_putendl_fd(ret, 2);
	}
	ft_strdel(&ret);
	ft_free2d(tableau);
}

void	env_gerror(int flag)
{
	if (flag)
	{
		ft_putstr_fd("\033[0;31msetenv: Variable name ", 2);
		ft_putendl_fd("must contain alphanumeric characters.\033[0m", 2);
	}
	else
		ft_putendl_fd("\033[0;31msetenv: Too many arguments.\033[0m", 2);
}

void	chdir_gerror(char *path, int flag)
{
	if (path == NULL)
		return ;
	if (flag == 0)
		ft_putstr_fd("cd: \033[0;31mnot a directory: \033[0m", 2);
	else if (flag == 1)
		ft_putstr_fd("cd: \033[0;31mpermission denied: \033[0m", 2);
	else if (flag == 2)
		ft_putstr_fd("cd: \033[0;31mno such file or directory: \033[0m", 2);
	ft_putstr_fd("\033[0;31m", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd("\033[0m", 2);
	ft_putchar_fd('\n', 2);
}

void	free_structure(t_holder *h, int flag)
{
	if (flag == 1)
	{
		free_list_mc(h->mclst);
		free_main_lst(h->lst);
	}
	ft_strdel(&h->ptr);
	free_list_env(&h->head_ref);
	if (h->stctmp)
		ft_strdel(&h->stctmp);
	ft_strdel(&h->history->path);
	ft_strdel(&h->line);
	free_list_alias(h->aliases);
	clear_hash(&h->hash);
	free(h);
}
