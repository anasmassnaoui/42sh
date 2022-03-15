/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhouiri <mhouiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:49:33 by mhouiri           #+#    #+#             */
/*   Updated: 2020/02/15 17:48:04 by mhouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t__mc		*build_node(char **cmd, int def, t__mc *next)
{
	t__mc *node;

	node = (t__mc *)malloc(sizeof(t__mc));
	node->cmd = cmd;
	node->def = def;
	node->next = next;
	return (node);
}

void		execute_fc(t_holder *h, t_bool background)
{
	t__mc	*mc_lst;
	t__mc	*mc_old_lst;

	if (ft_strlen(h->line))
	{
		if (background || h->pipe_exist)
		{
			h->pid_42sh = 0;
			h->mclst = mc_maker(h);
			command_handler(h, true);
		}
		else
		{
			mc_old_lst = h->current_mclst->next;
			h->current_mclst->next = build_node(NULL, 4, mc_maker(h));
			mc_lst = h->current_mclst->next;
			while (mc_lst->next)
				mc_lst = mc_lst->next;
			mc_lst->next = mc_old_lst;
		}
	}
}

int			ft_fc(char **cmd, t_all_hist *history, t_env *env_lst, t_holder *h)
{
	char	**tab_env;
	char	*str;
	char	*tmp;
	t_bool	background;

	str = ft_strdup("");
	history->x = 0;
	tab_env = get_env(&env_lst);
	if (history->lst)
	{
		tmp = ft_strdup(h->line);
		background = h->background;
		fc_command(&str, cmd, history, tab_env);
		ft_strdel(&h->line);
		store_in_file(str, history);
		store_line(history, str);
		h->line = ft_strdup(str);
		ft_strdel(&str);
		execute_fc(h, background);
		ft_free_tab2(tab_env);
		ft_strdel(&tmp);
		return (0);
	}
	else
		return (2);
}

int			fc_manager(t_holder *h, int status)
{
	if (h->history)
		status = ft_fc(h->lst->cmd, h->history, h->head_ref, h);
	return (status);
}
