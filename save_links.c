/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_links.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:58:17 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/15 15:12:51 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "lem_in.h"

BFS reading of links from the input
(read - que)


** Adds a double-link, meaning a link from the target room to the origin room
** by allocating the existing link_num amount (+ 1 for new link, +1 for NULL)
** of t_room pointers in an array, copies the existing links, adds the new
** link and ends the array in NULL.

void	make_double_link(t_room *room, t_room *origin)
{
	int 	j;
	t_room	**new;

	j = -1;
	if (room->links)
	{
		if (!(new = (t_room**)malloc(sizeof(t_room*) * (room->link_num + 2))))
			exit(0); //MALLOC ERROR
		while (++j < room->link_num)
			new[j] = room->links[j];
		new[j] = origin;
		new[j + 1] = NULL;
		room->links = new;
		room->link_num += 1;
	}
	else
	{
		if (!(room->links = (t_room**)malloc(sizeof(t_room*) * 2)))
			exit(0); //MALLOC ERROR
		room->links[0] = origin;
		room->links[1] = NULL;
	}
}

*/

