/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:07:40 by orantane          #+#    #+#             */
/*   Updated: 2020/10/29 16:44:42 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
        else if (cur)
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
                    free(read);
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

/*
** Creates an array, which we use to store all the paths we find. Also creates
** an array of int's which stores the index values for every search pass
** we do, so we know what paths were found on which ever pass.
*/

t_names     **make_path_array(t_lem *lem, t_room *start)
{
    t_names **arr;
	int		i;
    int     j;
    int     round;

    i = 0;
    round = 1;
	lem->max = lem->s_bneck * MAX_PATHS;
    if (!(arr = (t_names **)malloc(sizeof(t_names *) * lem->max + 1)))
        print_error(strerror(errno));
    init_arr_null(lem->max, arr);
    while(i < lem->max && round < ROUNDS)
    {
        j = round - 1;
        while (round < (j + 3) && i < lem->max && round < ROUNDS)
        {
            arr[i] = find_path(start);
            //if (lem->avoid_i != -1)
                //lem->avoid_i = return_shortest_path_to_use(start, lem->avoid_i);
            if (arr[i] == NULL)
            {
                if (i == 0)
                    print_error("ERROR! No possible paths");
                lem->pass[round] = i;
                init_next_pass(lem->pass[round - 1], lem->pass[round], arr);
                round++;
                continue ;
            }
            i++;
        }
        lem->value = path_select(lem, lem->pass, arr);
        if (lem->value && lem->required + 6 >= lem->value[2])
        {
            if (lem->flag_p == 1)
                print_path_array(arr, lem->pass);
            return (arr);
        }
        if (lem->value)
            free(lem->value);
        erase_avoids(lem->pass[j], lem->pass[round - 1], arr);
        lem->avoid_i = avoid_shortest_path(arr[lem->pass[j]]->room, start);
    }
    lem->value = path_select(lem, lem->pass, arr);
    if (lem->flag_p == 1)
        print_path_array(arr, lem->pass);
    return (arr);
}
