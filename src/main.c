/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:58:32 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/29 21:29:02 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Main first reads the input, saves it to a list. Then checks for errors in
** the input. If the input is correct, it is printed out. Creates the data
** structure for us to perform searches on. Then searches for the optimal
** solution. Once that is found, it prints it out in the right format.
*/

int	main(int argc, char **argv)
{
	t_list	*list;
	t_room	*room;
	t_lem	lem;
	t_names	**paths;

	init_lem_struct(&lem);
	while (--argc > 0)
		check_flags(&lem, argv[argc]);
	list = save_info(0);
	if (!list || list == NULL)
		print_error(strerror(errno));
	check_errors(list, &lem);
	list = print_input_data(list, &lem);
	room = room_names(list, &lem);
	build_link_tree(room, lem.links_begin, &lem);
	paths = make_path_array(&lem, room);
	print_output(&lem, paths);
	if (lem.flag_p == 1)
		print_path_array(paths, lem.pass);
	if (lem.flag_q == 1)
		ft_printf("Output is %d steps.\n", lem.step_count);
	return (0);
}
