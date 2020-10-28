/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:08:26 by orantane          #+#    #+#             */
/*   Updated: 2020/10/28 20:35:56 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int		strequ_n(char *room, char *link)
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

/*
** Initializes the variables in lem-struct.
*/

void	init_lem_struct(t_lem *lem)
{
	lem->ants = 0;
	lem->loop = 0;
	lem->s_bneck = 0;
	lem->value = NULL;
	lem->que = NULL;
	lem->read = NULL;
	lem->links_begin = NULL;
    lem->links_from_rm = NULL;
	lem->link = NULL;
	lem->cur = NULL;
	lem->tmp = NULL;
	lem->head = NULL;
    lem->avoid_i = -1;
	lem->required = 0;
	lem->flag_q = 0;
	lem->flag_p = 0;
	lem->step_count = 0;
}

void	check_flags(t_lem *lem, char *flag_str)
{
	int	i;
	
	i = -1;
	while (flag_str[++i])
	{
		if (flag_str[i] == 'q')
			lem->flag_q = 1;
		if (flag_str[i] == 'p')
			lem->flag_p = 1;
	}
}