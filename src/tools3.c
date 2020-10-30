/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:28:55 by orantane          #+#    #+#             */
/*   Updated: 2020/10/30 19:52:21 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_names	**mallocate_ant_array(t_lem *lem)
{
	t_names	**routes;

	if (!(routes = (t_names**)malloc(sizeof(t_names *) * (lem->ants + 1))))
		print_error(strerror(errno));
	routes[lem->ants] = NULL;
	return (routes);
}

int		*copy_value(int *value)
{
	int	*new;
	int	i;

	if (!(new = (int *)malloc(sizeof(int) * 3)))
		print_error(strerror(errno));
	i = 0;
	while (i < 3)
	{
		new[i] = value[i];
		i++;
	}
	return (new);
}

/*
** Checks if there were any flags used, saves the ones used.
*/

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
