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
** This function creates a linked list of all the rooms, one link for each
** room. "list" is the linked list that contains the input.
*/

t_room   *room_names(t_list *list, t_lem *lem)
{
	t_room	*head;
    t_room	*room;
	char	*str;

	head = NULL;
    while (list)
    {
		str = (char*)list->content;
		if (ft_isdigit(str[0]) && !ft_strchr(str, ' ') && !ft_strchr(str, '-'))
		{
			list = list->next;
			continue ;
		}
		if (!ft_strncmp(str, "##start", 7))
		{
            list = list->next;
			room = new_room_node((char*)list->content, 0);
            room_add(&head, room);
		}
		else if (!ft_strncmp(str, "##end", 5))
		{
            list = list->next;
			room = new_room_node((char*)list->content, 1);
		    room_add(&head, room);
		}
		else if (ft_strncmp(str, "#", 1) && ft_strchr(str, ' '))
		{
			room = new_room_node(str, 2);
		    room_add(&head, room);
		}
		else if (ft_strncmp(str, "#", 1) && !ft_strchr(str, ' '))
			break ;
        list = list->next;
    }
	lem->links = list;
	find_start_end(room);
	return (head);
}

/*
** Swaps the names of the two rooms, used to move rooms around.
*/

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

/*
** Finds the start and end rooms and puts them in the beginning of the
** linked list (start->end->[rest of the rooms]).
*/

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