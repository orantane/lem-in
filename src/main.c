/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:58:32 by ksalmi            #+#    #+#             */
/*   Updated: 2020/11/11 19:16:04 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Main first reads the input, saves it to a list. Then checks for errors in
** the input. If the input is correct, it is printed out. Creates the data
** structure for us to perform searches on. Then searches for the optimal
** solution. Once that is found, it prints it out in the correct format.
*/

static void	print_flags(t_lem *lem, t_names **paths)
{
	if (lem->flag_p == 1 && paths && lem->pass)
		print_path_array(paths, lem->pass);
	if (lem->flag_r == 1)
	{
		if (!lem->required)
			ft_printf("No required steps found for the output.");
		else
			ft_printf("Required amount of steps is %d.\n", lem->required);
	}
	if (lem->flag_q == 1 && lem->step_count)
		ft_printf("Output is %d steps.\n", lem->step_count);
	if (lem->flag_l == 1)
	{
		ft_putchar('\n');
		system("leaks lem-in");
	}
}

static void	print_help(void)
{
	ft_printf("Usage: ./lem-in [-pqrl] < 'input'\nFlag options are:\n");
	ft_printf("\t-q quiet mode, with only step count printed out.\n");
	ft_printf("\t-p prints all the paths found.\n");
	ft_printf("\t-r prints the required steps if there are any.\n");
	ft_printf("\t-l checks for memory leaks before program exits.\n");
	exit(0);
}

int			main(int argc, char **argv)
{
	t_list	*list;
	t_room	*room;
	t_lem	lem;
	t_names	**paths;

	init_lem_struct(&lem);
	while (--argc > 0)
		check_flags(&lem, argv[argc]);
	if (lem.flag_h)
		print_help();
	list = save_info(0);
	if (!list || list == NULL)
		print_error("ERROR! Empty or nonexisting file.");
	check_errors(list, &lem);
	if (!(list = print_input_data(list, &lem)))
		print_error("ERROR! Invalid input.");
	room = room_names(list, &lem);
	build_link_tree(room, lem.links_begin, &lem);
	paths = make_path_array(&lem, room);
	print_output(&lem, paths);
	print_flags(&lem, paths);
	exit(0);
}
