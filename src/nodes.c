/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:54:47 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/14 19:09:34 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Allocates a new node in memory and copies the name and
** the "start-end(se)" -number to the node. Also saves the
** X- and Y-coordinates needed for the visualizer.
*/

t_room	*new_name_node(char *content, int se)
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
	new->lnkd = 0;
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
** Adds a new t_name-node to the beginning of the linked list.
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