/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:38:19 by orantane          #+#    #+#             */
/*   Updated: 2020/11/11 19:10:45 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Uses sdbm hash-function to get the hash value from a room's name.
*/

int				get_hash(char *s)
{
	int					i;
	unsigned long int	hash;

	hash = 5381;
	while ((i = *s++))
		hash = ((hash << 5) + hash) + i;
	hash = hash % HASH_SIZE;
	return (hash);
}

/*
** This function creates a linked list of all the rooms, one link for each
** room. "list" is the linked list that contains the input.
*/

static t_room	*make_room_add_list(t_room *r, char *name, int se, t_lem *lem)
{
	t_room	*room;
	int		index;
	t_names	*cur;

	room = new_room_node(name, se);
	if (0 > (index = get_hash(room->name)))
		print_error("ERROR! Room name was NULL.");
	if (!(lem->hash_t[index]))
		lem->hash_t[index] = new_names_node(room, NULL);
	else
	{
		cur = lem->hash_t[index];
		while (cur->next)
			cur = cur->next;
		cur->next = new_names_node(room, NULL);
	}
	room_add(&r, room);
	return (r);
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
			head = make_room_add_list(head, (char*)list->content, 0, lem);
		}
		else if (!ft_strncmp((char*)list->content, "##end", 5))
		{
			list = list->next;
			head = make_room_add_list(head, (char*)list->content, 1, lem);
		}
		else if (ft_strncmp((char*)list->content, "#", 1) &&
			ft_strchr((char*)list->content, ' '))
			head = make_room_add_list(head, (char*)list->content, 2, lem);
		else if (ft_strncmp((char*)list->content, "#", 1)
			&& !ft_strchr((char*)list->content, ' '))
			break ;
		list = list->next;
	}
	lem->links_begin = list;
	return (find_start_end(head, lem));
}

/*
** Swaps the names of the two rooms, used to move rooms around.
*/

static t_room	*room_swap(t_room *head, t_room *end, t_room *start, t_lem *lem)
{
	if (!start || !end)
		print_error("ERROR! Invalid input.");
	end->next = head;
	start->next = end;
	lem->end = end;
	return (start);
}

/*
** Finds the start and end rooms and puts them in the beginning of the
** linked list (start->end->[rest of the rooms]).
*/

t_room			*find_start_end(t_room *room, t_lem *lem)
{
	t_ptrs	ptrs;

	ptrs.cur = room;
	ptrs.start = NULL;
	ptrs.end = NULL;
	ptrs.prev = NULL;
	while (ptrs.cur && (!ptrs.end || !ptrs.start))
	{
		if (ptrs.cur->se != 2)
		{
			if (ptrs.cur->se == 0)
				ptrs.start = ptrs.cur;
			else if (ptrs.cur->se == 1)
				ptrs.end = ptrs.cur;
			if (!ptrs.prev)
				room = ptrs.cur->next;
			else
				ptrs.prev->next = ptrs.cur->next;
		}
		if (ptrs.cur != ptrs.end && ptrs.cur != ptrs.start)
			ptrs.prev = ptrs.cur;
		ptrs.cur = ptrs.cur->next;
	}
	room = room_swap(room, ptrs.end, ptrs.start, lem);
	return (room);
}
