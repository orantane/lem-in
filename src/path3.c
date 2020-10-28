/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:07:40 by orantane          #+#    #+#             */
/*   Updated: 2020/10/28 15:52:32 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_names     *set_links_to_avoid(t_names *path)
{
    t_names *cur;
    t_names *origin;
    int     i;
    int     j;

    origin = path;
    while (origin->next)
    {
        i = 0;
        cur = origin->next;
		while (i < origin->room->link_num)
		{
            if (origin->room->links[i] == cur->room && cur->next)
            {
                origin->room->avoid[i] = 1;
                break ;
            }
            i++;
        }
        j = 0;
        while (j < cur->room->link_num)
        {
            if (cur->room->links[j] == origin->room)
            {
                cur->room->avoid[j] = 1;
                break ;
            }
            j++;
        }
        origin = origin->next;
    }
    return (path);
}

t_names     *create_path(t_names *search, t_room *start)
{
    t_names *cur;
    t_names *path;
    t_names *head;
    int     len;

    len = 0;
    head = NULL;
    path = new_names_node(search->room, search->room->origin);
    name_add(&head, path);
    while (search)
    {
        if (path->room->origin == start)
        {
            path->room->origin = NULL;
            head->len = len + 1;
            free_names_list(search);
            return (set_links_to_avoid(head));
        }
        cur = search->next;
        if (cur && cur->room == path->room->origin)
        {
            path = new_names_node(cur->room, cur->room->origin);
            path->room->vis = 1;
            
            name_add(&head, path);
            len++;
            if (head->next)
                head->next->room->origin = NULL;
        }
        else
            cur->room->origin = NULL;
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
            if (read->room->vis)
                read->room->origin = NULL;
            else
            {
                search = new_names_node(read->room, NULL);
                name_add(&head, search);
                if (search->room == start->next)
                {
                    free_names_list(que);
                    free_names_list(read->next);
                    return (create_path(search, start));
                }
                tmp = arr_to_list(search->room, search->room->link_num, 1);
                que = join_lists(tmp, que);
            }
            tmp = read->next;
            free(read);
            read = tmp;
        }
        read = que;
    }
    free_names_list(head);
    return (NULL);
}

void        init_next_pass(int start, int end, t_names **arr)
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
            cur = cur->next;
        }
        i++;
    }
}

int        avoid_shortest_path(t_room *short_path, t_room *start)
{
    int i;

    i = 0;
    while (i < start->link_num)
    {
        if (start->links[i] == short_path)
        {
            start->avoid[i] = 1;
            break ;
        }
        i++;
    }
    return (i);
}


void    erase_avoids(int start, int end, t_names **arr)
{
    int     i;
    int     j;
    t_names *cur;

    i = start;
    if (end != -1)
    {
        while (i <= end)
        {
            cur = arr[i];
            while (cur)
            {
                j = 0;
                while (j < cur->room->link_num)
                {
                    cur->room->avoid[j] = 0;
                    j++;
                }
                cur = cur->next;
            }
            i++;
        }
    }
}

static int     return_shortest_path_to_use(t_room *start, int avoid_i)
{
    start->avoid[avoid_i] = 0;
    return (-1);
}

/*
** Creates an array, which we use to store all the paths we find. Also creates
** an array of int's which stores the index values for every search pass
** we do, so we know what paths were found on which ever pass.
*/

t_names     **make_path_array(t_lem *lem, t_room *start)
{
    t_names **arr;
	int		max;
	int		i;
    int     j;
    int     pass[ROUNDS];
    int     round;
    int     avoid_i;

	i = -1;
    while (++i < ROUNDS)
        pass[i] = -1;
    pass[0] = 0;
    i = 0;
    round = 1;
	max = lem->s_bneck * MAX_PATHS;
    if (!(arr = (t_names **)malloc(sizeof(t_names *) * max + 1)))
        print_error(strerror(errno));
    init_arr_null(max, arr);
    avoid_i = -1;
    while(i < max && round < ROUNDS)
    {
        j = round - 1;
        while (round < (j + 3) && i < max && round < ROUNDS)
        {
            arr[i] = find_path(start);
            if (avoid_i != -1)
                avoid_i = return_shortest_path_to_use(start, avoid_i);
            if (arr[i] == NULL)
            {
                pass[round] = i;
                init_next_pass(pass[round - 1], pass[round], arr);
                round++;
                continue ;
            }
            i++;
        }
        lem->value = path_select(lem, pass, arr);
        if (lem->required + 6 >= lem->value[2])
            return (arr);
        free(lem->value);
        erase_avoids(pass[j], pass[round - 1], arr);
        avoid_i = avoid_shortest_path(arr[pass[j]]->room, start);
    }
    lem->value = path_select(lem, pass, arr);
    return (arr);
}
