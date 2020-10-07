/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 18:47:43 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/06 19:39:00 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_btree			*btree_create_node(int links_num, char *name)
{
	t_btree		**links;
	t_btree		*node;
	int			i;

	if (!(node = (t_btree*)malloc(sizeof(t_btree))))
		exit(0); //MALLOC ERROR (strerror(errno))
	if (!(links = (t_btree**)malloc(sizeof(t_btree*))))
		exit(0); //error
	i  = 0;
	while (i < links_num)
	{
		links[i] = NULL;
		i++;
	}
	if (name)
	{
		node->r_name = name;
		node->r_links = links;
		node->parent = NULL;
	}
	return (node);
}
