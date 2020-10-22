/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:07:40 by orantane          #+#    #+#             */
/*   Updated: 2020/10/22 21:18:07 by ksalmi           ###   ########.fr       */
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
            return (head);
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

/*void        init_next_pass(int start, int end, t_names **arr, t_room *r_end)
{
    int     i;
    t_names *cur;
    int     check;

    check = 0;
    i = start;
    while (i < end)
    {
        cur = arr[i];
        while (cur)
        {
            cur->room->vis = 0;
           if (check == 0 && cur->room != r_end && !cur->room->avoid)
           {
               cur->room->avoid = 1;
               check = 1;
           }
            cur = cur->next;
        }
        i++;
    }
}*/

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
    t_names **arr;
	int		max;
	int		i;
    int     pass[ROUNDS];
    int     round;

	i = -1;
    while (++i < ROUNDS)
        pass[i] = -1;
    pass[0] = 0;
    i = 0;
    round = 1;
	max = lem->s_bneck * MAX_PATHS;
    if (!(arr = (t_names **)malloc(sizeof(t_names *) * max + 1)))
        return (NULL); //Malloc error
    init_arr_null(max, arr);
    while (i < max && round < ROUNDS /* No more paths available! */)
	{
		arr[i] = find_path(start);
        /*if (arr[i] && check_all_avoids(arr[i], start->next))
        {
            free_names_list(arr[i]);
            arr[i] = NULL;
            break ;
        } */
		if (arr[i] == NULL)
        {
			pass[round] = i;
            init_next_pass(pass[round - 1], pass[round], arr, start->next);
            round++;
            continue ;
        }
        i++;
	}
   print_path_array(arr, pass); //only for checking, remove!
    lem->value = path_select(lem, pass, arr);
    return (arr);
}
