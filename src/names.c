/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:38:19 by orantane          #+#    #+#             */
/*   Updated: 2020/10/06 19:32:52 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** This function creates a linked list of all the room room. 
*/

t_room   *room_names(t_list *list, t_lem *lem)
{
	t_room	*head;
    t_room *room;

	head = NULL;
    while (list)
    {
		if (!ft_strncmp((char*)list->content, "##start", 7))
		{
            list = list->next;
			room = new_name_node((char*)list->content, 0);
            room_add(&head, room);
			lem->start = ft_strdup(room->name);
		}
		else if (!ft_strncmp((char*)list->content, "##end", 5))
		{
            list = list->next;
			room = new_name_node((char*)list->content, 1);
		    room_add(&head, room);
			lem->end = ft_strdup(room->name);
		}
		else if (ft_strncmp((char*)list->content, "#", 1) && ft_strchr((char*)list->content, ' '))
		{
			room = new_name_node((char*)list->content, 2);
		    room_add(&head, room);
		}
		else if (ft_strncmp(list->content, "#", 1) && !ft_strchr(list->content, ' '))
			break ;
        list = list->next;
    }
	lem->links = list;
	find_start_end(room);
	return (head);
}

static void	names_content_swap(t_room *room, t_room *node, int position)
{
	char	*str_tmp;
	int		se_tmp;

	if (position == 1 && room->next)
		room = room->next;
	str_tmp = ft_strdup(node->name);
	se_tmp = node->se;
	ft_strdel(&node->name);
	node->name = room->name;
	node->se = room->se;
	room->name = str_tmp;
	room->se = se_tmp;
}

void	find_start_end(t_room *room)
{
	t_room	*cur;

	cur = room;
	while (cur)
	{
		if (cur->se != 2)
		{
			if (cur->se == 0)
				names_content_swap(room, cur, 0);
			else
				names_content_swap(room, cur, 1);
		}
		cur = cur->next;
	}
}