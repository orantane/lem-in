/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:38:19 by orantane          #+#    #+#             */
/*   Updated: 2020/10/06 19:32:52 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** This function creates a linked list of all the room names. 
*/

t_names   *room_names(t_list *list, t_lem *lem)
{
	t_names	*head;
    t_names *names;
	t_names *temp;

	head = NULL;
    while (list)
    {
		if (!ft_strncmp((char*)list->content, "##start", 7))
		{
            list = list->next;
			names = new_name_node((char*)list->content, 0);
            names_add(&head, names);
		}
		else if (!ft_strncmp((char*)list->content, "##end", 5))
		{
            list = list->next;
			names = new_name_node((char*)list->content, 1);
		    names_add(&head, names);
		}
		else if (ft_strncmp((char*)list->content, "#", 1) && ft_strchr((char*)list->content, ' '))
		{
			names = new_name_node((char*)list->content, 2);
		    names_add(&head, names);
		}
		else if (ft_strncmp(list->content, "#", 1) && !ft_strchr(list->content, ' '))
			break ;
        list = list->next;
    }
	lem->links = list;
	find_start_end(names);
	return (head);
}

static void	names_content_swap(t_names *names, t_names *node, int position)
{
	char	*str_tmp;
	int		se_tmp;

	if (position == 1 && names->next)
		names = names->next;
	str_tmp = ft_strdup(node->name);
	se_tmp = node->se;
	ft_strdel(&node->name);
	node->name = names->name;
	node->se = names->se;
	names->name = str_tmp;
	names->se = se_tmp;
}

void	find_start_end(t_names *names)
{
	t_names	*cur;

	cur = names;
	while (cur)
	{
		if (cur->se != 2)
		{
			if (cur->se == 0)
				names_content_swap(names, cur, 0);
			else
				names_content_swap(names, cur, 1);
		}
		cur = cur->next;
	}
}