/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:54:47 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/22 16:23:04 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Allocates a new node in memory and copies the name and
** the "start-end(se)" -number to the node. Also saves the
** X- and Y-coordinates needed for the visualizer.
*/

t_room	*new_room_node(char *content, int se)
{
	t_room	*new;
	int		i;
	char	*tmp;

	i = 0;
	new = (t_room*)malloc(sizeof(t_room));
	if (!new)
		return (NULL);
	new->name = strcpy_space(content);
	tmp = ft_strchr(content, ' ');
	new->x = ft_atoi(tmp + 1);
	new->y = ft_atoi(ft_strchr((tmp + 1), ' '));
	new->se = se;
	new->origin = NULL;
	new->lnkd = 0;
	new->avoid = 0;
	new->lvl = -1;
	new->vis = 0;
	new->next = NULL;
	return (new);
}

/*
** Adds a new t_room-node to the beginning of the linked list.
*/

void	room_add(t_room **alst, t_room *new)
{
	if (new)
	{
		if (!*alst)
			*alst = new;
		else
		{
			new->next = *alst;
			*alst = new;
		}
	}
}

/*
** Creates a new t_names-node
*/

t_names		*new_names_node(t_room *room, t_room *origin)
{
	t_names	*node;

    if (!(node = (t_names *)malloc(sizeof(t_names))))
		print_error(strerror(errno));
	node->room = room;
	node->origin = origin;
	node->next = NULL;
	node->len = 0;
	return (node);
}

/*
** Adds a new t_names-node to the beginning of the linked list.
*/

void	name_add(t_names **alst, t_names *new)
{
	if (new)
	{
		if (!*alst)
			*alst = new;
		else
		{
			new->next = *alst;
			*alst = new;
		}
	}
}
