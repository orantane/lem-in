/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:07:40 by orantane          #+#    #+#             */
/*   Updated: 2020/10/29 21:48:33 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_names	*make_names_node_add_to_list(t_names *search, t_room *room)
{
	t_names *new;

	new = new_names_node(room, NULL);
	name_add(&search, new);
	return (search);
}

t_names			*create_path(t_names *search, t_room *start)
{
	t_names *cur;
	t_names *path;
	t_names *head;
	int     len;

	len = 0;
	head = NULL;
	path = new_names_node(search->room, search->room->origin);
	name_add(&head, path);
	while (search)
	{
		if (path->room->origin == start)
		{
			path->room->origin = NULL;
			head->len = len + 1;
			free_names_list(search);
			return (set_links_to_avoid(head));
		}
		cur = search->next;
		if (cur && cur->room == path->room->origin)
		{
			path = new_names_node(cur->room, cur->room->origin);
			path->room->vis = 1;
			name_add(&head, path);
			len++;
			if (head->next)
				head->next->room->origin = NULL;
		}
		else if (cur)
			cur->room->origin = NULL;
		free(search);
		search = cur;
	}
	return (NULL);
}

static int		found_end_room(t_names *head, t_room *end, t_lem *lem)
{
	int ret;

	ret = 0;
	if (head->room == end)
	{
		ret = 1;
		free_names_list(lem->que);
		free_names_list(lem->read->next);
		free(lem->read);
	}
	return (ret);
}

t_names			*find_path(t_room *start, t_lem *lem)
{
	t_names *search;

	lem->read = arr_to_list(start, start->link_num, 1);
	search = NULL;
	while (lem->read != NULL)
	{
		lem->que = NULL;
		while (lem->read != NULL)
		{
			if (lem->read->room->vis)
				lem->read->room->origin = NULL;
			else
			{
				search = make_names_node_add_to_list(search, lem->read->room);
				if (found_end_room(search, start->next, lem))
					return (create_path(search, start));
				lem->tmp = arr_to_list(search->room, search->room->link_num, 1);
				lem->que = join_lists(lem->tmp, lem->que);
			}
			lem->read = free_names_node_return_next(lem->read, lem->tmp);
		}
		lem->read = lem->que;
	}
	free_names_list(search);
	return (NULL);
}

void		next_pass(int start, int end, t_names **arr)
{
	int     i;
	t_names *cur;

	i = start;
	while (i < end)
	{
		cur = arr[i];
		while (cur)
		{
			cur->room->vis = 0;
			cur = cur->next;
		}
		i++;
	}
}

/*
** Creates an array, which we use to store all the paths we find. Also creates
** an array of int's which stores the index values for every search pass
** we do, so we know what paths were found on which ever pass.
*/


t_names		**make_path_array(t_lem *lem, t_room *start)
	{
	int		i;
	int		j;

	i = 0;
	init_lem_again(lem);
	while(i < lem->max && lem->r < ROUNDS)
	{
		j = lem->r - 1;
		while (lem->r < (j + 3) && i < lem->max && lem->r < ROUNDS)
		{
			lem->arr[i] = find_path(start, lem);
			if (lem->arr[i] == NULL)
			{
				if (i == 0)
					print_error("ERROR! No possible paths");
				lem->pass[lem->r] = i;
				next_pass(lem->pass[lem->r - 1], lem->pass[lem->r], lem->arr);
				lem->r++;
				continue ;
			}
			i++;
		}
		erase_avoids(lem->pass[j], lem->pass[lem->r - 1], lem->arr);
		if (lem->arr[lem->pass[j]])
			avoid_shortest_path(lem->arr[lem->pass[j]]->room, start);
	}
	lem->value = path_select(lem, lem->pass, lem->arr);
	return (lem->arr);
}
