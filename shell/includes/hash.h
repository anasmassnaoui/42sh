/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbenlarh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:41:51 by hbenlarh          #+#    #+#             */
/*   Updated: 2020/01/28 12:34:37 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# define SIZE_HASH 300

typedef struct	s_hash_cmd
{
	int					count;
	char				*cmd;
	char				*path;
	struct s_hash_cmd	*next;
}				t_hash_cmd;

typedef struct	s_hash
{
	t_hash_cmd	*liste[300];
	int			count;
	int			size;
}				t_hash;

void			add_in_hash(t_hash *hash, char *cmd, char *full_cmd, int i);
int				hash_str(char *cmd);
int				get_pow(int p, int i);
void			display_hash(t_hash hash);
int				hash_flags(t_hash *hash, char *flag,\
		char *next_flag, char *tmp);
int				hash_error_msg(char *flag);
char			*verify_if_exits(char *cmd, t_hash_cmd *hash);
void			clear_hash(t_hash *hash);
int				compare_builtin(char *cmd);

#endif
