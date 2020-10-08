/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:29:37 by orantane          #+#    #+#             */
/*   Updated: 2020/10/08 20:12:58 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Adds a new name-node to the beginning of the linked list.
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

/*
** Counts the amount of nodes in a linked list.
*/

int		count_links(t_names *links)
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

char	*strcpy_space(char *str)
{
	int		i;
	char	*new;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	if (!(new = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
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
	new->lvl = -1;
	new->next = NULL;
	return (new);
}

/*
** This function finds the room name the current room is connected to
** and returns the pointer to that name.
*/

char	*strstr_links(char *needle, char *haystack)
{
	int		i;
	char	*str;
	int		j;
	int		ret;

	i = 0;
	while (haystack[i] != '\0' && haystack[i] != '\n')
	{
		j = 0;
		while (haystack[i + j] == needle[j] ||
				(needle[j] == '\n' || needle[j] == '\0'))
		{
			if (!(i == 0 || (i > 0 && haystack[i - 1] == '-')))
				break ;
			if (needle[j] == '\0')
				return (NULL);
			j++;
			if ((needle[j] == '\0' || needle[j] == '\n') &&
				(haystack[i + j] == '\n' || haystack[i + j] == '\0'))
				return (haystack);
			else if ((needle[j] == '\0' || needle[j] == '\n') &&
					haystack[i + j] == '-')
				return (&haystack[i + j + 1]);
		}
		i++;
	}
	return (NULL);
}

void	print_everything(t_room *room, t_lem *lem)
{
	int	i;

	i = -1;
	if (!room)
		return ;
	if (!(ft_strcmp(room->name, lem->end)))
		return ;
	while (room->links[++i])
		printf("Room '%s' is on lvl '%d' and linked to room '%s'.\n", room->name, room->lvl, room->links[i]->name);
	i = -1;
	while (room->links[++i])
		print_everything(room->links[i], lem);
}