/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:58:32 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/07 15:43:46 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>
t_names     *find_links_to_room(char *r_name, t_list *list, t_names *names, char *ptr)
{
    t_names *links;
    t_names *head;
    t_names	*cur;

    head = NULL;
    while (list)
    {
        if ((ptr = strstr_links(r_name, (char*)list->content))) //pointer to part in content where r_name begins
        {
            cur = names;
            while (cur)
            {
                if (!ft_strncmp(ptr, cur->name, ft_strlen(cur->name)))
                {
                    if(!(links = (t_names*)malloc(sizeof(t_names))))
						return (NULL); //MALLOC ERROR
					links->name = cur->name;
					links->next = NULL;
					names_add(&head, links);
					break ;
        		}
				cur = cur->next;
            }
        }
        list = list->next;
    }
    return (head);
}

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


	list = save_info(0);
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
	btree_create_node(links_num, names->name);
//	lem.start = find_start_end(head, 1);
  //  lem.end = find_start_end(head, 2);
	return (0);
}