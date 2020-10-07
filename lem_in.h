/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:33:49 by orantane          #+#    #+#             */
/*   Updated: 2020/10/06 18:49:24 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

typedef struct		s_btree
{
	char			*r_name;
	struct s_btree	**r_links;	
	struct s_btree	*parent;
}					t_btree;

typedef struct		s_names
{
	char			*name;
	int				se;
	struct s_names	*next;
}					t_names;

typedef struct		s_lem
{
	int				ants;
	t_list			*links;
	char			*start;
	char			*end;
	struct s_btree	*rooms;
	char			*ptr;
}					t_lem;

t_list    			*save_info(int fd);
t_names				*new_name_node(char *content, int se);
char				*strcpy_space(char *str);
int     			count_links(t_names *links);
void				names_add(t_names **alst, t_names *new);
t_names  			 *room_names(t_list *list, t_lem *lem);
void				find_start_end(t_names *names);
char   				 *strstr_links(char *needle, char *haystack);

#endif
