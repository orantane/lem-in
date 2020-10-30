/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:53:16 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/30 19:59:33 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <stdlib.h>
# include <fcntl.h>
# include <sys/errno.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# define MAX_PATHS 5
# define ROUNDS 6
# define REQUIRED "#Here is the number of lines required: "

typedef struct		s_room
{
	char			*name;
	struct s_room	*origin;
	int				se;
	int				lnkd;
	int				vis;
	int				*avoid;
	int				x;
	int				y;
	int				link_num;
	struct s_room	**links;
	struct s_room	*next;
}					t_room;

typedef struct		s_names
{
	t_room			*room;
	t_room			*origin;
	int				len;
	struct s_names	*next;
}					t_names;

typedef struct		s_value
{
	int				mod;
	int				tmp_ants;
	int				start;
	int				end;
}					t_value;

typedef struct		s_print
{
	t_names			**routes;
	int				print;
	int				tmp_ants;
	int				j;
	int				i;
}					t_print;

typedef struct		s_prep
{
	t_names			**routes;
	int				i;
	int				j;
	int				tmp_ants;
	int				*tmp_value;
}					t_prep;

typedef struct		s_lem
{
	int				ants;
	t_list			*links_begin;
	int				loop;
	int				s_bneck;
	int				i;
	int				j;
	int				tmp_i;
	int				tmp_j;
	int				*value;
	t_names			*que;
	t_names			*read;
	t_names			*tmp;
	t_names			*head;
	t_names			*link;
	t_names			*links_from_rm;
	t_names			*pt;
	t_names			*root;
	t_room			*cur;
	char			*end;
	int				max;
	char			*tmp_str;
	int				required;
	int				flag_q;
	int				flag_p;
	int				step_count;
	int				*pass;
	int				r;
	t_names			**arr;
}					t_lem;

/*
** tools.c file contains functions:
*/

t_names				*arr_to_list(t_room *room, int link_num, int avoid);
void				free_names_list(t_names *list);
int					count_links(t_names *links);
char				*strcpy_space(char *str);
char				*strstr_links(char *needle, char *haystack);

/*
** tools2.c file contains functions:
*/

void				init_arr_null(int num, t_names **arr);
int					strequ_n(char *room, char *link);
void				init_lem_struct(t_lem *lem);
void				init_lem_again(t_lem *lem);
void				check_flags(t_lem *lem, char *flag_str);
t_names				*free_names_node_return_next(t_names *to_free,
						t_names *tmp);

/*
** tools3.c file contains functions:
*/

int					*copy_value(int *value);
t_names				**mallocate_ant_array(t_lem *lem);

/*
** avoid.c file contains functions:
*/

t_names				*set_links_to_avoid(t_names *path);
void				avoid_shortest_path(t_room *short_path, t_room *start);
void				erase_avoids(int start, int end, t_names **arr);

/*
** build_link_tree.c file contains the function:
*/

void				links_to_room(t_room *cur, t_room *rooms, t_names *links);
void				build_link_tree(t_room *start, t_list *list, t_lem *lem);

/*
** error.c file contains functions:
*/

void				print_error(char *str);
void				check_errors(t_list *list, t_lem *lem);

/*
** links.c file contains functions:
*/

t_names				*join_lists(t_names *new, t_names *old);
t_names				*find_links(t_room *room, t_list *list, \
						t_room *all, t_lem *lem);

/*
** names.c file contains functions:
*/

t_room				*room_names(t_list *list, t_lem *lem);
t_room				*find_start_end(t_room *room);

/*
** nodes.c file contains functions:
*/

t_room				*new_room_node(char *content, int se);
t_names				*new_names_node(t_room *room, t_room *origin);
void				name_add(t_names **alst, t_names *new);
void				room_add(t_room **alst, t_room *new);
t_names				*addn(t_names *head, t_room *room, t_room *orig);

/*
** path_select.c file contains functions:
*/

void				pass_sort_paths_len(t_names **arr, int start, int end);
int					*path_select(t_lem *lem, int *pass, t_names **arr);
int					*pass_value(int ants, t_names **arr, int start, int end);

/*
** path.c file contains functions:
*/

t_names				*create_path(t_names *search, t_room *start,
						t_lem *lem, int len);
t_names				*find_path(t_room *start, t_lem *lem);
void				next_pass(int start, int end, t_names **arr);
t_names				**make_path_array(t_lem *lem, t_room *start);

/*
** print.c file contains functions:
*/

t_names				**prepare_output(t_lem *lem, t_names **paths);
void				print_output(t_lem *lem, t_names **paths);
t_list				*print_input_data(t_list *list, t_lem *lem);
void				print_path_array(t_names **arr, int *rounds);

/*
** save_info.c file contains functions:
*/

t_list				*save_info(int fd);

#endif
