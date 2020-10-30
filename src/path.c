/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:07:40 by orantane          #+#    #+#             */
/*   Updated: 2020/10/30 17:51:07 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Creates the path found by the "find_path"function. Backtracks from the end
** using the origin pointers in the room structs. Frees the memory allocations
** for structs that are not in the path, but were created while doing the BFS.
** Also sets the origin rooms to NULL.
*/

t_names		*create_path(t_names *search, t_room *start, t_lem *lem, int len)
{
	lem->root = NULL;
	lem->root = addn(lem->root, search->room, search->room->origin);
	while (search)
	{
		if (lem->root->room->origin == start)
		{
			lem->root->room->origin = NULL;
			lem->root->len = len + 1;
			free_names_list(search);
			return (set_links_to_avoid(lem->root));
		}
		lem->tmp = search->next;
		if (lem->tmp && lem->tmp->room == lem->root->room->origin)
		{
			lem->root = addn(lem->root, lem->tmp->room, lem->tmp->room->origin);
			lem->root->room->vis = 1;
			len++;
			if (lem->root->next)
				lem->root->next->room->origin = NULL;
		}
		else if (lem->tmp)
			lem->tmp->room->origin = NULL;
		search = free_names_node_return_next(search, lem->tmp);
	}
	return (NULL);
}

static int	found_end_room(t_names *head, t_room *end, t_lem *lem)
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

/*
** Performs a BFS to find the available paths. Once the BFS finds the
** end, it backtracks the route to create a linked list path.
*/

t_names		*find_path(t_room *start, t_lem *lem)
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
				search = addn(search, lem->read->room, NULL);
				if (found_end_room(search, start->next, lem))
					return (create_path(search, start, lem, 0));
				lem->pt = arr_to_list(search->room, search->room->link_num, 1);
				lem->que = join_lists(lem->pt, lem->que);
			}
			lem->read = free_names_node_return_next(lem->read, lem->pt);
		}
		lem->read = lem->que;
	}
	free_names_list(search);
	return (NULL);
}

/*
** Goes through the paths found in the search pass that just ended,
** and sets the rooms back to unvisited.
*/

void		next_pass(int start, int end, t_names **arr)
{
	int		i;
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
	lem->i = 0;
	init_lem_again(lem);
	while (lem->i < lem->max && lem->r < ROUNDS)
	{
		lem->j = lem->r - 1;
		while (lem->r < (lem->j + 3) && lem->i < lem->max && lem->r < ROUNDS)
		{
			lem->arr[lem->i] = find_path(start, lem);
			if (lem->arr[lem->i] == NULL)
			{
				if (lem->i == 0)
					print_error("ERROR! No possible paths");
				lem->pass[lem->r] = lem->i;
				next_pass(lem->pass[lem->r - 1], lem->pass[lem->r], lem->arr);
				lem->r++;
				continue ;
			}
			lem->i++;
		}
		erase_avoids(lem->pass[lem->j], lem->pass[lem->r - 1], lem->arr);
		if (lem->arr[lem->pass[lem->j]])
			avoid_shortest_path(lem->arr[lem->pass[lem->j]]->room, start);
	}
	lem->value = path_select(lem, lem->pass, lem->arr);
	return (lem->arr);
}
