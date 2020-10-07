/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:58:32 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/07 20:31:14 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Function takes the room we want to add links to, the list of all the rooms
** (*rooms) the t_names list of rooms to be linked, and the number of links.
** The function allocates memory for the link array and sets the links[i] to
** point to the rooms found in the t_names *links.
*/
void    build_links_to_room(t_room *cur, t_room *rooms, t_names *links, int num)
{
    t_names	*tmp;
	int		i;
	t_names	*new;

	if (!(cur->links = (t_room**)malloc(sizeof(t_room*) * (num + 1))))
		return (NULL); //MALLOC ERROR
	i = 0;
    while (rooms && i < num)
    {
		tmp = links;
		while (tmp)
		{
			if (tmp->room == rooms)
			{
				cur->links[i] = rooms;
				i++;
			}
			tmp = tmp->next;
		}
		rooms = rooms->next;
	}
	cur->links[i] = NULL;
}

/*
** Function takes the name of the room whose links we want to find (r_name), the gnl list
** starting from the first line with info about a link and the linked list of
** with all the rooms. Find_links_to_room makes a linked list of t_names (which
** has a ptr to t_room struct). The list will have all the rooms that have
** a link from r_name.
*/

t_names     *find_links_to_room(char *r_name, t_list *list, t_room *rooms)
{
    t_names *links;
    t_names	*head;
    t_room	*cur;
	char	*tmp;

    head = NULL;
    while (list)
    {
        if ((tmp = strstr_links(r_name, (char*)list->content)))
        {
            cur = rooms;
            while (cur)
            {
                if (!ft_strncmp(tmp, cur->name, ft_strlen(cur->name)))
                {
                    if(!(links = (t_names*)malloc(sizeof(t_names))))
						return (NULL); //MALLOC ERROR
					links->room = cur;
					links->next = NULL;
					room_add(&head, links);
					tmp = ft_strchr(list->content, '-');
					tmp[0] = '+';
					break ;
        		}
				cur = cur->next;
            }
        }
        list = list->next;
    }
    return (head);
}

/*
** So far this function only handles the starting room, meaning
** that it gets a list of rooms connected to it, counts the
** number of those connections and builds the links.
** Maybe the *links could be our queue where we read from.
*/

void	build_link_tree(t_room *start, t_room *rooms, t_list *list)
{
	t_names *links;
	int		links_num;
	int		i;
	t_names	*read;
	t_names	*que;
								//start huone
	links = find_links_to_room(start->name, list, rooms);
	links_num = count_links(links);
	build_links_to_room(start, rooms, links, links_num);
	//looppi

	//2 linked lists: Queue Visited
	//aluks Queue on links

	// read = links;
	

	// while (read)
	// {
	// 	links = find_links_to_room(start->links[i]->name, list, rooms);
	// 	links_num = count_links(links);
	// 	build_links_to_room(start->links[i], rooms, links, links_num);
	// 	i++;
	// 	while (que && que->next)
			
		//yhdistä juuri saatu links que:n loppuun


	// start->links[0]->links[i]
	// start->links[0]->links[i]-name
	// free(links);

}

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


	list = save_info(0);
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
	build_link_tree(room, room, list);

//	lem.start = find_start_end(head, 1);
  //  lem.end = find_start_end(head, 2);
	return (0);
}