/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:13:51 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/30 19:56:30 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_names			*join_lists(t_names *new, t_names *old)
{
	t_names	*cur;

	if (!new)
		return (old);
	if (!old)
		return (new);
	else
	{
		cur = new;
		if (cur->next == NULL)
			cur->next = old;
		else
		{
			while (cur->next)
				cur = cur->next;
			cur->next = old;
		}
		return (new);
	}
}

/*
** Function takes the name of the room whose links we want to find (r_name),
** the gnl list starting from the first line with info about a link and the
** linked list with all the rooms. Find_links_to_room makes a linked list of
** t_names (which has a ptr to t_room struct). The list will have all the rooms
** that have a link from r_name.
*/

t_names			*find_links(t_room *room, t_list *list, t_room *all, t_lem *lem)
{
	lem->head = NULL;
	while (list)
	{
		if ((lem->tmp_str = strstr_links(room->name, (char*)list->content)))
		{
			lem->cur = all;
			while (lem->cur)
			{
				if (lem->cur != all && strequ_n(lem->cur->name, lem->tmp_str))
				{
					if (!(lem->link = (t_names*)malloc(sizeof(t_names))))
						print_error(strerror(errno));
					lem->link->room = lem->cur;
					lem->link->origin = room;
					lem->link->next = NULL;
					name_add(&lem->head, lem->link);
					break ;
				}
				lem->cur = lem->cur->next;
			}
		}
		list = list->next;
	}
	return (lem->head);
}
