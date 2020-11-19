/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:42:55 by ksalmi            #+#    #+#             */
/*   Updated: 2020/11/11 19:10:44 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** These functions read the input line by line and saves it to a linked list.
*/

static t_list	*set_tail(t_list *tail, t_list *new)
{
	tail->next = new;
	tail = new;
	return (tail);
}

t_list			*save_info(int fd)
{
	t_list	*head;
	t_list	*tail;
	t_list	*new;
	char	*line;
	int		ret;

	head = NULL;
	tail = NULL;
	while ((ret = get_next_line(fd, &line) == 1))
	{
		new = ft_lstnew(line, ft_strlen(line) + 1);
		if (head == NULL)
		{
			head = new;
			tail = new;
		}
		else
			tail = set_tail(tail, new);
		if (line)
			ft_strdel(&line);
	}
	if (ret == -1)
		print_error(strerror(errno));
	return (head);
}
