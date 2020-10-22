/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:58:32 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/22 15:11:46 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main()
{
	t_list  *list;
	t_list  *head;
	t_room *room;
	t_lem   lem;
	t_names	**paths;
	

	if (argc > 1)
	{
		list = save_info(0);
		head = list;
		// while (list)		// Prints out the whole input.
		// {
		// 	ft_printf("%s", list->content);
		// 	list = list->next;
		// }
		//ft_putchar('\n');
		head = ants_amount(head, &lem);		// Saves the amount of ants.
		room = room_names(head, &lem);	// Creates and initializes the big room structure.
		// cur = room;
		// while (cur)
		// {
		// 	ft_printf("name: %s\n", cur->name);
		// 	cur = cur->next;
		// }
		lem.ptr = NULL;
		build_link_tree(room, room, lem.links, &lem);
		//maybe make a check to see that all rooms have been linked and there are no "solitary" ones
		//in this case, error invalid file?
		paths = make_path_array(&lem, room);
		print_output(&lem, paths);
		//print_everything(room, &lem);
	//	lem.start = find_start_end(head, 1);
	//  lem.end = find_start_end(head, 2);
	}
	return (0);
}