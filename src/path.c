/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:07:40 by orantane          #+#    #+#             */
/*   Updated: 2020/10/14 21:21:45 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_names     *create_path(t_names *search, t_room *start)
{
    t_names *cur;
    t_names *path;
    t_names *head;

    head = NULL;
    if (!(path = (t_names *)malloc(sizeof(t_names))))
        return (NULL); //MALLOC ERROR
    path->room = search->room;
    path->origin = search->origin;
    path->next = NULL;
    name_add(&head, path);
    while (search)
    {
        if (path->origin == start)
        {
            free_names_list(search);
            return (head);
        }
        cur = search->next;
        free(search);
        if (cur && cur->room == path->origin)
        {
            if (!(path = (t_names *)malloc(sizeof(t_names))))
                return (NULL); //MALLOC ERROR
            path->room = cur->room;
            path->origin = cur->origin;
            path->next = NULL;
            name_add(&head, path);
        }
        search = cur;
    }
    return (NULL);
}

t_names     *find_path(t_room *start)
{
    t_names *search;
    t_names *head;
    t_names *read;
    t_names *que;
    t_names *tmp;

    read = arr_to_list(start, start->link_num);
    head = NULL;
    while (read != NULL)
    {
        que = NULL;
        while (read != NULL)
        {
            if (read->room->vis)
            {
                read = read->next;
                continue ;
            }
            if (!(search = (t_names *)malloc(sizeof(t_names))))
                return (NULL); //MALLOC ERROR
            search->room = read->room;
            search->next = NULL;
            search->origin = read->origin;
            name_add(&head, search);
            if (search->room == start->next)
                return (create_path(search, start));
            search->room->vis = 1; //do this in create_path
            tmp = arr_to_list(search->room, search->room->link_num);
            que = join_lists(tmp, que);
            tmp = read->next;
            free(read);
            read = tmp;
        }
        read = que;
    }
    free_names_list(head);
    return (NULL);
}


t_names     **make_path_array(t_lem *lem, t_room *start)
{
    t_room  *cur;
    t_names **arr;
	int		max;
	int		i;
    t_names *tmp;

	i = 0;
	max = lem->s_bneck * MAX_PATHS;
    if (!(arr = (t_names **)malloc(sizeof(t_names *) * max + 1)))
        return (NULL); //Malloc error
    init_arr_null(max, arr);
    cur = start;
    while (i < max /* No more paths available! */)
	{
		arr[i] = find_path(start);
		if (arr[i] == NULL)
			break ; // Currently only does one pathfinding pass of the tree.
        i++;
	}
    i = 0;
    //only for printing, take away
    while (arr[i])
    {
        tmp = arr[i];
        while (tmp)
        {
            ft_printf("%s->", tmp->room->name);
            tmp = tmp->next;
        }
        ft_printf("\n");
        i++;
    }
    return (arr);
}
