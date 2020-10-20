/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:03:20 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/20 19:48:16 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

t_names		**prepare_output(t_lem *lem, t_names **paths)
{
	t_names	**routes;
	int		i;
	int		j;
	int		tmp_ants;
	int		*tmp_value;

	if (!(routes = (t_names**)malloc(sizeof(t_names *) * lem->ants + 1)))
		exit(0); //MALLOC ERROR
	routes[lem->ants] = NULL;
	i = -1;
	tmp_ants = lem->ants;
	if (!(tmp_value = (int *)malloc(sizeof(int) * 3))) // This is not free'd at any point.
        return (0); // MALLOC ERROR!!
	while (++i < 3)
		tmp_value[i] = lem->value[i];
	i = 0;
	while (i < lem->ants)
	{
		tmp_value = pass_value(tmp_ants, paths, tmp_value[0], tmp_value[1]++);
		tmp_ants = tmp_ants - (tmp_value[1] - tmp_value[0] + 1);
		j = tmp_value[0];
		while (j <= tmp_value[1])
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
		lem->value = pass_value(lem->ants, paths, lem->value[0], lem->value[1]++);
		lem->ants = lem->ants - (lem->value[1] - lem->value[0] + 1);
		print = j + (lem->value[1] - lem->value[0]);
		// if (print > lem->ants)
		// 	print = lem->ants;
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