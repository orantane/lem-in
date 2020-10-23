/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:58:32 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/23 21:39:33 by ksalmi           ###   ########.fr       */
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

	init_lem_struct(&lem);
	list = save_info(0);
	if (!list || list == NULL)
		print_error(strerror(errno));
	check_errors(list, &lem);
	head = list;
	while (list)		// Prints out the whole input.
	{
		ft_putendl((char*)list->content);
		list = list->next;
	}
	ft_putchar('\n');
	room = room_names(head, &lem);	// Creates and initializes the big room structure.
	lem.ptr = NULL;
	build_link_tree(room, room, lem.links, &lem);
	paths = make_path_array(&lem, room);
	print_output(&lem, paths);
	return (0);

}