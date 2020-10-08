#include "lem_in.h"
#include <stdio.h>

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
	int		fd;


	fd = open(argv[1], O_RDONLY);
	list = save_info(fd);
	head = list;
	while (list)		// Prints out the whole input.
	{
		ft_printf("%s", list->content);
		list = list->next;
	}
	lem.ants = ft_atoi(head->content);		// Saves the amount of ants.
	room = room_names(head->next, &lem);	// Creates and initializes the big room structure.
	cur = room;
	while (cur)
	{
		ft_printf("name: %s\n", cur->name);
		cur = cur->next;
	}
	lem.ptr = NULL;
	build_link_tree(room, room, lem.links, &lem);
	int i = 0;
	print_everything(room, &lem);
//	lem.start = find_start_end(head, 1);
  //  lem.end = find_start_end(head, 2);
	return (0);
}