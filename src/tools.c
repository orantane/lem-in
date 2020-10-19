/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:29:37 by orantane          #+#    #+#             */
/*   Updated: 2020/10/19 15:41:04 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Finds and saves the number of ants into t_lem struct ignoring comment lines
** and returning the list from where the room names should begin.
*/

t_list		*ants_amount(t_list *list, t_lem *lem)
{
	char	*str;

	while (list)
	{
		str = (char*)list->content;
		if (str[0] == '#')
		{
			list = list->next;
			continue ;
		}
		if (!ft_isdigit(str[0]))
			exit(0); //error wrong format
		lem->ants = ft_atoi(list->content);
		break;
	}
	return (list->next);
}

/*
** Makes the rooms links-array into a t_names linked list.
** After the first pass, avoids previously used rooms by using the
** "avoid" variable. If all the "child" rooms are rooms to be avoided,
** it doesn't avoid any of them.
*/

t_names     *arr_to_list(t_room *room, int link_num, int avoid)
{
    int     i;
    t_names *head;
    t_names *new;

	head = NULL;
	head = NULL;
	head = NULL;
    i = 0;
	while (room->links[i] && i < link_num)
    {
		if (room->links[i]->origin != NULL || room->links[i]->avoid == avoid || \
			 room->links[i]->vis == 1)
		{
			i++;
			continue ;
		}
		if (!(new = (t_names *)malloc(sizeof(t_names))))
			return (NULL); //MALLOC ERROR
		new->room = room->links[i];
		if (new->room->origin == NULL)
			new->room->origin = room;
		new->next = NULL;
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

void	free_names_list(t_names *list)
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
** This function finds the room name the current room is connected to
** and returns the pointer to that name.
*/

char	*strstr_links(char *needle, char *haystack)
{
	int		i;
	int		j;

	i = 0;
	while (haystack[i] != '\0' && haystack[i] != '\n')
	{
		j = 0;
		while (needle[j] && haystack[i + j] && haystack[i + j] == needle[j])
		{
			if (!(i == 0 || (i > 0 && haystack[i - 1] == '-')))
				break ;
			if (needle[j] == '\0' && (haystack[i + j] == '\n' || \
				haystack[i + j] == '\0' || haystack[i + j] == '-'))
				break ;
			j++;
			if (needle[j] == '\0' && (haystack[i + j] == '\n' || haystack[i + j] == '\0'))
				return (haystack);
			else if ((needle[j] == '\0' || needle[j] == '\n') &&
					haystack[i + j] == '-')
				return (&haystack[i + j + 1]);
		}
		i++;
	}
	return (NULL);
}

/*
** Sets the given pointer array to 0's.
*/

void	init_arr_null(int num, t_names **arr)
{
	int	i;

	i = 0;
	while (i < num)
	{
		arr[i] = NULL;
		i++;
	}
	arr[i] = NULL;
}

int		strequ_newline(char *room, char *link)
{
	unsigned int	i;

	i = 0;
	while ((room[i] && link[i] && room[i] == link[i]))
		i++;
	if ((!room[i] && !link[i]) || (!room[i] && link[i] == '\n') || \
		(!room[i] && link[i] == '-'))
		return (1);
	return (0);
}

int		check_all_avoids(t_names *path, t_room *end)
{
	while (path)
	{
		if (path->room->avoid == 0)
			break;
		path = path->next;
	}
	if (path->room == end)
		return (1);
	else
		return (0);
}