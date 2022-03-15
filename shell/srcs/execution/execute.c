/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myamani <myamani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:56:52 by aariss            #+#    #+#             */
/*   Updated: 2020/02/02 21:26:37 by myamani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*execute_error(char *arg, char *path)
{
	char		*msgerror;
	char		*tempo;
	struct stat	buffer;
	int			i;

	i = stat(arg, &buffer);
	msgerror = NULL;
	if (arg && access(path, F_OK) != 0 && !ft_strncmp(arg, "./", 2))
	{
		tempo = ft_strjoin("42sh: ", arg);
		msgerror = ft_strjoin_f(tempo, ": No such file or directory", 1);
	}
	else if (i != -1 && S_ISDIR(buffer.st_mode))
		msgerror = ft_strjoin(arg, ": is a directory");
	else if (access(path, F_OK) == -1)
		msgerror = ft_strjoin("command not found: ", arg);
	else if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
		msgerror = ft_strjoin("permission denied: ", arg);
	return (msgerror);
}

void	execute(char **command, char *path_found, pid_t *get, t_holder *h)
{
	char		**env;

	env = get_env(&h->head_ref);
	h->error = execute_error(command[0], path_found);
	*get = execute_handler(path_found, command, env, h);
	ft_strdel(&path_found);
	ft_free2d(env);
}

char	**get_path(t_env **head_ref)
{
	t_env	*current;

	current = *head_ref;
	while (current)
	{
		if (ft_strcmp(current->var, "PATH") == 0)
			return (ft_strsplit(current->value, ':'));
		current = current->next;
	}
	return (NULL);
}

void	add_node_1(t_env *curr, t_env *new_node)
{
	while (curr->next)
		curr = curr->next;
	curr->next = new_node;
}
