/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aariss <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:14:46 by aariss            #+#    #+#             */
/*   Updated: 2020/01/28 12:14:54 by aariss           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBING_H
# define GLOBING_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <dirent.h>
# include "libft.h"

typedef struct stat			t_stat;
typedef struct dirent		t_dirent;
typedef struct s_content	t_content;
typedef struct s_map		t_map;

struct		s_map
{
	int		word_start;
	int		word_end;
	char	*wild;
	char	*directory;
	char	*hint;
	int		type_hint;
};

struct		s_content
{
	char		*name;
	int			type;
	t_content	*next;
};

t_map		get_wild(const char *line, int cursor);
t_content	*get_files_list(t_map wild_map);
char		*wild_monkey(t_content *lst, char *line, t_map wild_map);

/*
** List related Funcs
*/

t_content	*fill_list(DIR *directory, t_map wild_map);

/*
** Extra Funcs
*/

char		*ft_joinchar_glob(char *s, char c);

/*
** get_hint_and_dirs.c
*/

char		*get_splited_word_globing(char *wild, char key);
t_map		get_ground_hint_globing(char *wild);
int			verify_type_of(char *hint);

/*
** find_match.c
*/
int			count_until(char *hint);
int			find_match(char *name, char *hint);
int			wild_found(char *str, int curs);
int			is_wild(char character);
int			is_bracket_wild(const char *line, size_t cursor);
int			is_valid_bracket(const char *wild, int cursor);
int			is_wild(char character);
int			ft_isquote_glob(int c);
int			match_glob(char *string, char *hint);
void		characters_match(char **string, char **hint);
int			asterisk_match(char **string, char **hint);
void		after_asterisk(char **string, char **hint);
void		question_match(char **string, char **hint);
int			bracket_match(char **string, char **hint);
int			bracket_one_char_match(char **string, char **hint);
int			bracket_reverse_char_match(char **string, char **hint);
int			bracket_coma_match(char **string, char **hint);
int			bracket_dash_match(char **string, char **hint);
int			seer(const char *hint);
char		**range_maker(char *hint);
int			special_count(const char *hint);
int			is_bracket_wild(const char *line, size_t cursor);
int			opened_bracket(const char *wild, int *cursor);
t_map		init_map(void);
t_map		map_create(const char *line, int count, int cursor, int end);
DIR			*open_this(char *directory);
int			wild_quote_skipper(const char *line, size_t cursor);
int			is_wild_token(char c);

#endif
