/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_link_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:43:25 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/29 21:48:28 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** So far this function only handles the starting room, meaning
** that it gets a list of rooms connected to it, counts the
** number of those connections and builds the links.
** Maybe the *links could be our queue where we read from.
*/

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
