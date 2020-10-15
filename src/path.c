/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:07:40 by orantane          #+#    #+#             */
/*   Updated: 2020/10/15 18:24:46 by ksalmi           ###   ########.fr       */
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
    path->room->origin = search->room->origin;
    path->next = NULL;
    name_add(&head, path);
    while (search)
    {
        if (path->room->origin == start)
        {
            path->room->origin = NULL;
            free_names_list(search);
            return (head);
        }
        cur = search->next;
        if (cur && cur->room == path->room->origin)
        {
            if (!(path = (t_names *)malloc(sizeof(t_names))))
                return (NULL); //MALLOC ERROR
            path->room = cur->room;
            path->room->origin = cur->room->origin;
            path->next = NULL;
            path->room->vis = 1;
            name_add(&head, path);
            if (head->next)
                head->next->room->origin = NULL;
        }
        else
            cur->room->origin = NULL; // Does not set all origins to NULL, needs to be fixed!!!
        free(search);
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

    read = arr_to_list(start, start->link_num, 1);
    head = NULL;
    while (read != NULL)
    {
        que = NULL;
        while (read != NULL)
        {
            if (read->room->vis) //|| read->room->origin != NULL)
            {
                read = read->next;
                continue ;
            }
            if (!(search = (t_names *)malloc(sizeof(t_names))))
                return (NULL); //MALLOC ERROR
            search->room = read->room;
            search->next = NULL;
            name_add(&head, search);
            if (search->room == start->next)
                return (create_path(search, start));
            tmp = arr_to_list(search->room, search->room->link_num, 1);
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

void        init_next_pass(int start, int end, t_names **arr, t_room *r_end)
{
    int     i;
    t_names *cur;

    i = start;
    while (i < end)
    {
        cur = arr[i];
        while (cur)
        {
            cur->room->vis = 0;
            if (cur->room != r_end)
                cur->room->avoid = 1;
            cur = cur->next;
        }
        i++;
    }
}

t_names     **make_path_array(t_lem *lem, t_room *start)
{
    t_room  *cur;
    t_names **arr;
	int		max;
	int		i;
    t_names *tmp;
    int     pass[10000];
    int     round;

	i = -1;
    while (++i < 10000)
        pass[i] = 0;
    i = 0;
    round = 1;
	max = lem->s_bneck * MAX_PATHS;
    if (!(arr = (t_names **)malloc(sizeof(t_names *) * max + 1)))
        return (NULL); //Malloc error
    init_arr_null(max, arr);
    cur = start;
    while (i < max /* No more paths available! */)
	{
		arr[i] = find_path(start);
		if (arr[i] == NULL)
        {
			pass[round] = i;
            init_next_pass(pass[round - 1], pass[round], arr, start->next);
            round++;
            
        }
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
