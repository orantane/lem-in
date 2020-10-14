/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:33:49 by orantane          #+#    #+#             */
/*   Updated: 2020/10/14 15:04:21 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h> // REMOVE BEFORE TURNING IN!
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

typedef struct		s_room
{
	char			*name;
	int				se;
	int				lvl;
	int				unq;
	int				avoid;
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
	struct s_names	*next;
}					t_names;


typedef struct		s_lem
{
	int				ants;
	int				lvl;
	int				s_bneck;
	int				e_bneck;
	t_names			*que;
	t_names			*read;
	t_list			*links;
	char			*start;
	char			*end;
	char			*ptr;
}					t_lem;

t_list    			*save_info(int fd);
t_room				*new_name_node(char *content, int se);
char				*strcpy_space(char *str);
int     			count_links(t_names *links);
void				name_add(t_names **alst, t_names *new);
void				room_add(t_room **alst, t_room *new);
t_room 				*room_names(t_list *list, t_lem *lem);
void				find_start_end(t_room *room);
char   				*strstr_links(char *needle, char *haystack);
void				links_to_room(t_room *cur, t_room *rooms, t_names *links);
t_names     		*find_links_to_room(t_room *room, t_list *list, t_room *all, t_lem *lem);
void				build_link_tree(t_room *start, t_room *rooms, t_list *list,
					t_lem *lem);
t_names				*join_lists(t_names *new, t_names *old);
void				make_double_link(t_room *room, t_room *origin);
void				print_everything(t_room *room, t_lem *lem);
int					strequ_newline(char *room, char *link);
#endif
