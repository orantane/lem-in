/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:13:51 by ksalmi            #+#    #+#             */
/*   Updated: 2020/11/11 19:10:46 by ksalmi           ###   ########.fr       */
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
** linked list with all the rooms. Find_links makes a linked list of
** t_names (which has a ptr to t_room struct). The list will have all the rooms
** that have a link from r_name.
*/

t_names			*find_links(t_room *room, t_list *list, t_room *all, t_lem *lem)
{
	int		index;
	t_names	*cur;
	char	*tmp_str;

	lem->head = NULL;
	while (list)
	{
		lem->cnt = (char*)list->content;
		if ((tmp_str = strstr_lnk(room->name, lem->cnt)) && lem->cnt[0] != '#')
		{
			index = get_hash(tmp_str);
			cur = lem->hash_t[index];
			if (!cur)
				print_error("ERROR! Invalid link to nonexistant room");
			while (cur && ft_strcmp(cur->room->name, tmp_str))
				cur = cur->next;
			if (cur->room != all)
				name_add(&lem->head,
				(lem->link = new_names_node(cur->room, room)));
		}
		if (tmp_str)
			ft_strdel(&tmp_str);
		list = list->next;
	}
	return (lem->head);
}
