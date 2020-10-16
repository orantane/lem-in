/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:03:20 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/16 20:46:56 by ksalmi           ###   ########.fr       */
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
