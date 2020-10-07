#include "lem_in.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	t_list  *list;
	t_list  *head;
	t_names *names;
	t_names	*cur;
	t_lem   lem;
	char    **arr;
	t_names	*links_from_room;
	int		links_num;
    int      fd;

    fd = open(argv[1], O_RDONLY);
	list = save_info(fd);
	head = list;
	while (list)
	{
		ft_printf("%s", list->content);
		list = list->next;
	}
	lem.ants = ft_atoi(head->content);
	names = room_names(head->next, &lem);
    cur = names;
	while (cur)
	{
		ft_printf("name: %s\n", cur->name);
		cur = cur->next;
	}
    lem.ptr = NULL;
	links_from_room = find_links_to_room(names->name, lem.links, names, lem.ptr);
	links_num = count_links(links_from_room);
	while (links_from_room)
	{
		ft_printf("name: %s\n", links_from_room->name);
		links_from_room = links_from_room->next;
	}
	ft_printf("number of links:%d\n", links_num);
	
	//find_links_to_room(char *r_name, t_list *list, t_names *names)
//	lem.start = find_start_end(head, 1);
  //  lem.end = find_start_end(head, 2);
	return (0);
}