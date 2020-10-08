/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <oskari.rantanen@student.hive.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:33:49 by orantane          #+#    #+#             */
/*   Updated: 2020/10/08 16:01:05 by orantane         ###   ########.fr       */
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

// typedef struct		s_btree
// {
// 	char			*r_name;
// 	struct s_btree	**r_links;	
// 	//struct s_btree	**parent;
// }					t_btree;

typedef struct		s_room
{
	char			*name;
	int				se;
	int				lvl;
	int				x;
	int				y;
	struct s_room	**links;
	struct s_room	*next;
}					t_room;

typedef struct		s_names
{
	t_room			*room;
	//char			*name;
	struct s_names	*next;
}					t_names;


typedef struct		s_lem
{
	int				ants;
	int				link_num;
	struct t_names	*que;
	struct t_names	*read;
	t_list			*links;
	char			*start;
	char			*end;
	struct s_btree	*rooms;
	char			*ptr;
}					t_lem;

t_list    			*save_info(int fd);
t_room				*new_name_node(char *content, int se);
char				*strcpy_space(char *str);
int     			count_links(t_room *links);
void				names_add(t_room **alst, t_room *new);
t_room 				*room_names(t_list *list, t_lem *lem);
void				find_start_end(t_room *room);
char   				*strstr_links(char *needle, char *haystack);

#endif
