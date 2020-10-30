/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:38:19 by orantane          #+#    #+#             */
/*   Updated: 2020/10/30 17:42:47 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** This function creates a linked list of all the rooms, one link for each
** room. "list" is the linked list that contains the input.
*/

static t_room	*make_room_node_add_to_list(t_room *head, char *name, int se)
{
	t_room *room;

	room = new_room_node(name, se);
	room_add(&head, room);
	return (head);
}

t_room			*room_names(t_list *list, t_lem *lem)
{
	t_room	*head;

	head = NULL;
	while (list)
	{
		if (!ft_strncmp((char*)list->content, "##start", 7))
		{
			list = list->next;
			head = make_room_node_add_to_list(head, (char*)list->content, 0);
		}
		else if (!ft_strncmp((char*)list->content, "##end", 5))
		{
			list = list->next;
			head = make_room_node_add_to_list(head, (char*)list->content, 1);
		}
		else if (ft_strncmp((char*)list->content, "#", 1) &&
			ft_strchr((char*)list->content, ' '))
			head = make_room_node_add_to_list(head, (char*)list->content, 2);
		else if (ft_strncmp((char*)list->content, "#", 1) &&
			!ft_strchr((char*)list->content, ' '))
			break ;
		list = list->next;
	}
	lem->links_begin = list;
	return (find_start_end(head));
}

/*
** Swaps the names of the two rooms, used to move rooms around.
*/

static void		names_content_swap(t_room *room, t_room *node, int position)
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

t_room			*find_start_end(t_room *room)
{
	t_room	*head;
	t_room	*cur;

	head = room;
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
	return (head);
}
