/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_link_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:43:25 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/30 19:57:10 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Function takes the room we want to add links to, the list of all the rooms
** (*rooms) the t_names list of rooms to be linked, and the number of links.
** The function allocates memory for the link array and sets the links[i] to
** point to the rooms found in the t_names *links.
*/

static void		set_status(t_room *cur, int i)
{
	cur->links[i] = NULL;
	cur->avoid[i] = -1;
	cur->lnkd = 1;
}

void			links_to_room(t_room *cur, t_room *rooms, t_names *links)
{
	t_names	*tmp;
	int		i;

	if (!(cur->links = (t_room**)malloc(sizeof(t_room*) * (cur->link_num + 1))))
		print_error(strerror(errno));
	if (!(cur->avoid = (int*)malloc(sizeof(int) * (cur->link_num + 1))))
		print_error(strerror(errno));
	i = 0;
	while (rooms && i < cur->link_num)
	{
		tmp = links;
		while (tmp)
		{
			if (tmp->room == rooms)
			{
				cur->links[i] = rooms;
				cur->avoid[i] = 0;
				i++;
			}
			tmp = tmp->next;
		}
		rooms = rooms->next;
	}
	set_status(cur, i);
}

static t_names	*links_from_start_room(t_room *start, t_list *list, t_lem *lem)
{
	t_names	*links;

	links = find_links(start, list, start, lem);
	start->link_num = count_links(links);
	lem->s_bneck = start->link_num;
	links_to_room(start, start, links);
	return (links);
}

void			build_link_tree(t_room *start, t_list *list, t_lem *lem)
{
	lem->read = links_from_start_room(start, list, lem);
	while (lem->read != NULL)
	{
		lem->que = NULL;
		while (lem->read != NULL)
		{
			if (lem->read->room->lnkd || (lem->read->room != NULL &&
				lem->read->room == start->next))
			{
				lem->read = free_names_node_return_next(lem->read, lem->tmp);
				continue ;
			}
			lem->links_from_rm = find_links(lem->read->room, list, start, lem);
			if (lem->links_from_rm)
			{
				lem->read->room->link_num = count_links(lem->links_from_rm);
				links_to_room(lem->read->room, start, lem->links_from_rm);
			}
			lem->que = join_lists(lem->links_from_rm, lem->que);
			lem->read = free_names_node_return_next(lem->read, lem->tmp);
		}
		lem->read = lem->que;
	}
}
