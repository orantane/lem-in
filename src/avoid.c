/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avoid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:52:59 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/28 20:30:30 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_names		*set_links_to_avoid(t_names *path)
{
	t_names	*cur;
	t_names *origin;
	int		i;
	int		j;

	origin = path;
	while (origin->next)
	{
		i = -1;
		cur = origin->next;
		while (++i < origin->room->link_num)
		{
			if (origin->room->links[i] == cur->room && cur->next)
				origin->room->avoid[i] = 1;
		}
		j = -1;
		while (cur->next && ++j < cur->room->link_num)
		{
			if (cur->room->links[j] == origin->room)
				cur->room->avoid[j] = 1;
		}
		origin = origin->next;
	}
	return (path);
}

int			avoid_shortest_path(t_room *short_path, t_room *start)
{
	int	i;

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

void		erase_avoids(int start, int end, t_names **arr)
{
	int		i;
	int		j;
	t_names	*cur;

	i = start;
	if (end != -1)
	{
		while (i <= end)
		{
			cur = arr[i];
			while (cur && cur->room)
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

int			return_shortest_path_to_use(t_room *start, int avoid_i)
{
	start->avoid[avoid_i] = 0;
	return (-1);
}
