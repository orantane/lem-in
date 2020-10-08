/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <oskari.rantanen@student.hive.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:41:48 by orantane          #+#    #+#             */
/*   Updated: 2020/10/08 16:01:02 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_names		*build_queue(t_room *cur, t_room *rooms, t_names *links, t_lem *lem)
{
	t_names	*queue;
	int		i;

	i = -1;
	if (!(queue = (t_names *)malloc(sizeof(t_names))))
		exit(1);
	names_add(lem->que, rooms);
	return (queue);
}