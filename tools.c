/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:29:37 by orantane          #+#    #+#             */
/*   Updated: 2020/10/07 15:43:46 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

/*
** Adds a new name-node to the beginning of the linked list.
*/

void	names_add(t_names **alst, t_names *new)
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

int     count_links(t_names *links)
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
** Allocates a new node in memory and copies the name and the "start-end(se)" -number to the node.
*/

t_names	*new_name_node(char *content, int se)
{
	t_names	*new;

	new = (t_names*)malloc(sizeof(t_names));
	if (!new)
		return (NULL);
	new->name = new->name = strcpy_space(content);
    new->se = se;
	new->next = NULL;
	return (new);
}


char    *strstr_links(char *needle, char *haystack)
{
	int		i;
	char	*str;
	int		j;
	int		ret;

	i = 0;
	if (!needle || *needle == '\n')
		return (NULL);
	while (haystack[i] != '\0' && haystack[i] != '\n')
    {
    	j = 0;
		while (haystack[i + j] == needle[j] || 
				(needle[j] == '\n' || needle[j] == '\0'))
		{
			if (!(i == 0 || (i > 0 && haystack[i - 1] == '-')))
				break ;
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