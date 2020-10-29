/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi		    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:33:49 by orantane          #+#    #+#             */
/*   Updated: 2020/10/29 16:35:42 by ksalmi           ###   ########.fr       */
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
	int				tmp_i;
	int				tmp_j;
	int				*value;
	t_names			*que;
	t_names			*read;
	t_names			*tmp;
	t_names			*head;
	t_names			*link;
	t_names			*links_from_rm;
	t_room			*cur;
	char			*end;
	int				max;
	char			*tmp_str;
	int				required;
	int				flag_q;
	int				flag_p;
	int				step_count;
	int     		*pass;
	int				r;
	t_names			**arr;
}					t_lem;

void				init_lem_struct(t_lem *lem);
t_list    			*save_info(int fd);
void				check_errors(t_list *list, t_lem *lem);
t_room				*new_room_node(char *content, int se);
t_names				*new_names_node(t_room *room, t_room *origin);
char				*strcpy_space(char *str);
int     			count_links(t_names *links);
void				name_add(t_names **alst, t_names *new);
void				room_add(t_room **alst, t_room *new);
t_room 				*room_names(t_list *list, t_lem *lem);
t_room				*find_start_end(t_room *room);
char   				*strstr_links(char *needle, char *haystack);
void				links_to_room(t_room *cur, t_room *rooms, t_names *links);
t_names     		*find_links(t_room *room, t_list *list, \
						t_room *all, t_lem *lem);
void				build_link_tree(t_room *start, t_list *list, t_lem *lem);
t_names				*join_lists(t_names *new, t_names *old);
int					strequ_n(char *room, char *link);
void				init_arr_null(int num, t_names **arr);
void				free_names_list(t_names *list);
t_names     		*arr_to_list(t_room *room, int link_num, int avoid);
t_names				**make_path_array(t_lem *lem, t_room *start);
void				init_lem_again(t_lem *lem);
t_names    			*find_path(t_room *start, t_lem *lem);
t_names     		*create_path(t_names *search, t_room *start);
void        		next_pass(int start, int end, t_names **arr);
int					check_all_avoids(t_names *path, t_room *end);
int					max_flow_pass(int *pass, int i);
void    			pass_sort_paths_len(t_names **arr, int start, int end);
int					*path_select(t_lem *lem, int *pass, t_names **arr);
int					*pass_value(int ants, t_names **arr, int start, int end);
int					max_flow_pass(int *pass, int i);
t_names				**prepare_output(t_lem *lem, t_names **paths);
void				print_output(t_lem *lem, t_names **paths);
t_names     		*set_links_to_avoid(t_names *path);
void        		avoid_shortest_path(t_room *short_path, t_room *start);
t_list				*print_input_data(t_list *list, t_lem *lem);
void				print_error(char *str);
void    			print_path_array(t_names **arr, int *rounds);
void				check_flags(t_lem *lem, char *flag_str);
int     			return_shortest_path_to_use(t_room *start, int avoid_i);
void    			erase_avoids(int start, int end, t_names **arr);
t_names				*free_names_node_return_next(t_names *to_free, t_names *tmp);

#endif
