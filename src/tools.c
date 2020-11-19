/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:40:51 by ksalmi            #+#    #+#             */
/*   Updated: 2020/11/11 19:10:47 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Makes the rooms links-array into a t_names linked list.
** After the first pass, avoids previously used rooms by using the
** "avoid" variable. If all the "child" rooms are rooms to be avoided,
** it doesn't avoid any of them.
*/

t_names		*arr_to_list(t_room *room, int link_num, int avoid)
{
	int		i;
	t_names *head;
	t_names *new;

	head = NULL;
	i = 0;
	if (room->link_num == 0)
		return (head);
	while (i < room->link_num && room->links[i])
	{
		if (room->links[i]->origin != NULL || room->avoid[i] == avoid || \
			room->links[i]->vis == 1)
		{
			i++;
			continue ;
		}
		new = new_names_node(room->links[i], NULL);
		if (new->room->origin == NULL)
			new->room->origin = room;
		name_add(&head, new);
		i++;
	}
	if (room->links[0] && !head && avoid == 1)
		head = arr_to_list(room, link_num, 0);
	return (head);
}

/*
** Free a t_names linked list.
*/

void		free_names_list(t_names *list)
{
	t_names	*tmp;

	while (list)
	{
		if (list->room->origin)
			list->room->origin = NULL;
		tmp = list->next;
		free(list);
		list = tmp;
	}
	list = NULL;
}

/*
** Counts the amount of nodes in a linked list.
*/

int			count_links(t_names *links)
{
	int i;

	i = 0;
	while (links)
	{
		i++;
		links = links->next;
	}
	return (i);
}

/*
** Copies the source string content to a new allocated string up until
** '\0' or 'space' character. Room names always end with a space.
*/

char		*strcpy_space(char *str)
{
	int		i;
	char	*new;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	if (!(new = (char *)malloc(sizeof(char) * (i + 1))))
		print_error(strerror(errno));
	i = 0;
	while (str[i] != ' ')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

/*
** This function finds the room name the current room is connected to
** and returns the pointer to that name.
*/

char		*strstr_lnk(char *needle, char *haystack)
{
	int		i;
	int		j;

	check_link_format(haystack);
	i = 0;
	while (haystack[i] != '\0')
	{
		j = 0;
		while (needle[j] && haystack[i + j] && haystack[i + j] == needle[j])
		{
			if (!(i == 0 || (i > 0 && haystack[i - 1] == '-')))
				break ;
			if (needle[j] == '\0' && (haystack[i + j] == '\0' ||
				haystack[i + j] == '-'))
				break ;
			j++;
			if (needle[j] == '\0' && haystack[i + j] == '\0')
				return (ft_strsub(haystack, 0, (size_t)(i - 1)));
			else if (needle[j] == '\0' && haystack[i + j] == '-')
				return (ft_strdup(&haystack[i + j + 1]));
		}
		i++;
	}
	return (NULL);
}
