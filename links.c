/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 17:46:02 by orantane          #+#    #+#             */
/*   Updated: 2020/10/08 20:40:50 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_names		*join_lists(t_names *new, t_names *old)
{
	t_names	*cur;

	if (!new)
		return (NULL);
	if (!old)
		return (new);
	else
	{
		cur = new;
		if (cur->next == NULL)
			cur->next = old;
		else
		{
			while (cur->next)
				cur = cur->next;
			cur->next = old;
		}
		return (cur);
	}
}

/*
** Function takes the room we want to add links to, the list of all the rooms
** (*rooms) the t_names list of rooms to be linked, and the number of links.
** The function allocates memory for the link array and sets the links[i] to
** point to the rooms found in the t_names *links.
*/
void    links_to_room(t_room *cur, t_room *rooms, t_names *links, t_lem *lem)
{
    t_names	*tmp;
	int		i;
	t_names	*new;

	if (!(cur->links = (t_room**)malloc(sizeof(t_room*) * (lem->link_num + 1))))
		exit(0); //MALLOC ERROR
	i = 0;
	cur->lvl = lem->lvl;
    while (rooms && i < lem->link_num)
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
** Function takes the name of the room whose links we want to find (r_name),
** the gnl list starting from the first line with info about a link and the
** linked list with all the rooms. Find_links_to_room makes a linked list of
** t_names (which has a ptr to t_room struct). The list will have all the rooms
** that have a link from r_name.
*/

t_names     *find_links_to_room(char *r_name, t_list *list, t_room *rooms)
{
    t_names *links;
    t_names	*head;
    t_room	*cur;
	char	*tmp;

//suojaa needle, jos on tyhja tai \n
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
					name_add(&head, links);
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

void	build_link_tree(t_room *start, t_room *rooms, t_list *list, t_lem *lem)
{
	t_names *links;
	t_names	*tmp;
	t_names	*que;
	t_names	*read;

	lem->lvl = 0;
	read = NULL;
	links = find_links_to_room(start->name, list, rooms);
	lem->link_num = count_links(links);
	read = links;
	links_to_room(start, rooms, links, lem);
	while (read != NULL)
	{
		que = NULL;
        lem->lvl++;
		while (read != NULL)
		{
			if (!(ft_strcmp(read->room->name, lem->end)) && read->room != NULL)
			{
				tmp = read->next;
				free(read);
				read = tmp;
				continue ;
			}
			links = find_links_to_room(read->room->name, list, rooms);
            if (links)
            {
                lem->link_num = count_links(links);
                links_to_room(read->room, rooms, links, lem);
            }
			que = join_lists(links, que);
            tmp = read->next;
            free(read);
            read = tmp;
		}
		read = que;
	}
}