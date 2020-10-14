/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:58:32 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/14 19:10:37 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(int argc, char **argv)
{
	t_list  *list;
	t_list  *head;
	t_room *room;
	t_lem   lem;
	char    **arr;
	t_room	*links_from_room;
	t_room	*cur;
	int		links_num;

	lem.s_bneck = 0;
	lem.e_bneck = 0;
	list = save_info(0);
	head = list;
	while (list)		// Prints out the whole input.
	{
		ft_printf("%s", list->content);
		list = list->next;
	}
//	lem.ants = ft_atoi(head->content);		// Saves the amount of ants.
	room = room_names(head->next, &lem);	// Creates and initializes the big room structure.
	cur = room;
	while (cur)
	{
		ft_printf("name: %s\n", cur->name);
		cur = cur->next;
	}
	lem.ptr = NULL;
	build_link_tree(room, room, list, &lem);

//	lem.start = find_start_end(head, 1);
  //  lem.end = find_start_end(head, 2);
	return (0);
}