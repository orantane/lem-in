/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:29:37 by orantane          #+#    #+#             */
/*   Updated: 2020/10/14 20:04:36 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**  Makes the rooms links-array into a t_names linked list.
*/

t_names     *arr_to_list(t_room *room, int link_num)
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
        if (!(new = (t_names *)malloc(sizeof(t_names))))
            return (NULL); //MALLOC ERROR
        new->room = room->links[i];
		new->origin = room;
		new->next = NULL;
        name_add(&head, new);
        i++;
    }
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
			if (needle[j] == '\0' && (haystack[i + j] == '\n' || haystack[i + j] == '\0' || haystack[i + j] == '-'))
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

void	print_everything(t_room *room, t_lem *lem)
{
	int	i;

	i = -1;
	if (!room)
		return ;
	if (!(ft_strcmp(room->name, lem->end)))
		return ;
	while (room->links && room->links[++i])
		printf("Room '%s' is on lvl '%d' and linked to room '%s'.\n", room->name, room->lvl, room->links[i]->name);
	i = -1;
	while (room->links && room->links[++i])
	{
		if (room->links[i]->lvl != room->lvl)
			print_everything(room->links[i], lem);
	}
}

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