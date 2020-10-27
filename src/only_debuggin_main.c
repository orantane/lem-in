#include "lem_in.h"

int		main(int argc, char **argv)
{
	t_list  *list;
	t_list  *head;
	t_room *room;
	t_lem   lem;
	//t_room	*cur;
	int		fd;
	t_names	**paths;
	
	init_lem_struct(&lem);
	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
			print_error(strerror(errno));
		list = save_info(fd);
		if (!list || list == NULL)
			print_error(strerror(errno));
		head = list;
		check_errors(list, &lem);
		while (list)		// Prints out the whole input.
		{
			ft_putendl((char*)list->content);
			list = list->next;
		}
		ft_putchar('\n');
		room = room_names(head, &lem);	// Creates and initializes the big room structure.
		// cur = room;
		// while (cur)
		// {
		// 	ft_printf("name: %s\n", cur->name);
		// 	cur = cur->next;
		// }
		build_link_tree(room, room, lem.links, &lem);
		//maybe make a check to see that all rooms have been linked and there are no "solitary" ones
		//in this case, error invalid file?
		paths = make_path_array(&lem, room);
		print_output(&lem, paths);
	}
	//while(1) ;
	return (0);
}
