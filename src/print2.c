/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>	    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:03:20 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/21 19:34:46 by orantane         ###   ########.fr       */
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
		print_error(strerror(errno));
	routes[lem->ants] = NULL;
	i = -1;
	tmp_ants = lem->ants;
	if (!(tmp_value = (int *)malloc(sizeof(int) * 3))) // This is not free'd at any point.
		print_error(strerror(errno));
	while (++i < 3)
		tmp_value[i] = lem->value[i];
	i = 0;
	while (i < lem->ants)
	{
		tmp_value = pass_value(tmp_ants, paths, tmp_value[0], (tmp_value[1] + 1));
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
	int		tmp_ants;
	int		lines;

	lines = 0;
	i = 0;
	j = 0;
	lem->loop = 1;
	routes = prepare_output(lem, paths);
	tmp_ants = lem->ants;
	while (lem->loop)
	{
		lem->loop = 0;
		lem->value = pass_value(tmp_ants, paths, lem->value[0], (lem->value[1]) + 1);
		tmp_ants = tmp_ants - (lem->value[1] - lem->value[0] + 1);
		print = j + (lem->value[1] - lem->value[0] + 1);
		//ft_printf("Value[0]:%d, value[1]:%d, value[2]:%d, j:%d, print:%d\n", lem->value[0], lem->value[1], lem->value[2], j, print);
		if (print > lem->ants)
		 	print = lem->ants;
		j = 0;
		while (print && j < print)
		{
			if (routes[j] != NULL)
				ft_printf("L%d-%s ", (j + 1), routes[j]->room->name);
			if (routes[j] != NULL)
			{
				routes[j] = routes[j]->next;
				if (routes[j] != NULL)
					lem->loop = 1;
			}
			j++;
		}
		//j++;
		ft_putchar('\n');
		lines++;
	}
	//ft_printf("\nPRINTED LINES: %d\n", lines);
}