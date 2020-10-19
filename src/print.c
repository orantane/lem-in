/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:03:20 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/19 17:40:26 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*void	print_ants_mov(t_names **arr, int start, int end, t_lem *lem)
{
	int		i;
	int		j;
	int		ants;
	int		flow;
	t_names	*cur[end - start];

	flow = end - start;
	i = start;
	while (ants < lem->ants)
	{
		j = 0;
		while (j < flow)
		{
			cur[j] = arr[i];
			ants = j + 1;
			ft_printf("L%d-%s ", ants, cur[j]->room->name);
			j++;
			i++;
		}
	}


L1-1 L2-2
L1-4 L3-1 L2-3
L3-4 L2-4
} */


void    print_path_array(t_names **arr, int *pass)
{
    int     i;
	int		j;
	int		flow;
    t_names *tmp;

    i = 0;
	j = 0;
	flow = 0;
    while (arr[i] && j < ROUNDS && (j == 0 || pass[j] != 0))
    {
		ft_printf("Round:%d, pass[j]=%d flow:%d\n", j, pass[j],  pass[j + 1] - pass[j]);
		while (arr[i] && i < pass[j + 1])
		{
			tmp = arr[i];
			while (tmp)
			{
				ft_printf("%s->", tmp->room->name);
				tmp = tmp->next;
			}
			ft_printf("  |  %d is path len.\n", arr[i]->len);
			i++;
		}
		j++;
    }
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
		printf("Room '%s' is on lvl '%d' and linked to room '%s'.\n", \
			room->name, room->lvl, room->links[i]->name);
	i = -1;
	while (room->links && room->links[++i])
	{
		if (room->links[i]->lvl != room->lvl)
			print_everything(room->links[i], lem);
	}
}
t_names		**prepare_output(t_lem *lem, t_names **paths)
{
	t_names	**routes;
	int		i;
	int		j;

	if (!(routes = (t_names**)malloc(sizeof(t_names *) * lem->ants + 1)))
		exit(0); //MALLOC ERROR
	routes[lem->ants] = NULL;
	i = 0;
	while (i < lem->ants)
	{
		j = lem->value[0];
		while (j <= lem->value[1])
		{
			routes[i] = paths[j];
			j++;
			i++;
		}
	}
	return (routes);
}

void	print_output(t_lem *lem, t_names **paths)
{
	t_names	**routes;
	int		i;
	int		j;
	int		print;
	int		loop;

	i = 0;
	j = 1;
	loop = 1;
	routes = prepare_output(lem, paths);
	while (loop)
	{
		loop = 0;
		print = j + (lem->value[1] - lem->value[0]);
		if (print > lem->ants)
			print = lem->ants;
		j = -1;
		while(++j < print && print)
		{
			if (routes[j] != NULL)
				ft_printf("L%d-%s ", (j + 1), routes[j]->room->name);
			if (routes[j] != NULL)
			{
				routes[j] = routes[j]->next;
				loop = 1;
			}
		}
		j++;
		if (loop)
			ft_putchar('\n');
	}
}