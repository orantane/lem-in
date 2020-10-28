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
		ft_printf("\nRound:%d, paths found:%d\n", j, pass[j + 1] - pass[j]);
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
	ft_putchar('\n');
}

/*
** Creates an array of pointers to paths. Each pointer represents an ant.
** So there are as many pointers as there are ants. Uses the pass_value
** function to evaluate the paths for each ant. Returns the allocated
** array to be printed.
*/

t_names		**prepare_output(t_lem *lem, t_names **paths)
{
	t_names	**routes;
	int		i;
	int		j;
	int		tmp_ants;
	int		*tmp_value;

	if (!(routes = (t_names**)malloc(sizeof(t_names *) * (lem->ants + 1))))
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
		lem->tmp_i = tmp_value[0];
		lem->tmp_j = tmp_value[1];
		free(tmp_value);
		tmp_value = pass_value(tmp_ants, paths, lem->tmp_i, lem->tmp_j + 1);
		tmp_ants = tmp_ants - (tmp_value[1] - tmp_value[0] + 1);
		j = tmp_value[0];
		while (j <= tmp_value[1])
		{
			routes[i] = paths[j];
			j++;
			i++;
		}
	}
	free(tmp_value);
	return (routes);
}

/*
** Prints the result in the correct format. Uses the pass_value
** function to dynamically adjust the amount printed per each
** step.
*/

void	print_output(t_lem *lem, t_names **paths)
{
	t_names	**routes;
	int		i;
	int		j;
	int		print;
	int		tmp_ants;

	i = 0;
	j = 0;
	lem->loop = 1;
	routes = prepare_output(lem, paths);
	tmp_ants = lem->ants;
	while (lem->loop)
	{
		lem->loop = 0;
		lem->tmp_i = lem->value[0];
		lem->tmp_j = lem->value[1];
		if (lem->value)
			free(lem->value);
		lem->value = pass_value(tmp_ants, paths, lem->tmp_i, lem->tmp_j + 1);
		tmp_ants = tmp_ants - (lem->value[1] - lem->value[0] + 1);
		print = j + (lem->value[1] - lem->value[0] + 1);
		if (print > lem->ants)
		 	print = lem->ants;
		j = 0;
		while (print && j < print)
		{
			if (routes[j] != NULL && lem->flag_q == 0)
				ft_printf("L%d-%s ", (j + 1), routes[j]->room->name);
			if (routes[j] != NULL)
			{
				routes[j] = routes[j]->next;
				if (routes[j] != NULL)
					lem->loop = 1;
			}
			j++;
		}
		if (lem->flag_q == 0)
			ft_putchar('\n');
		else
			lem->step_count++;
	}
	free(lem->value);
	free(routes);
}

t_list	*print_input_data(t_list *list, t_lem *lem)
{
	t_list	*after_ant_num;
	char	*str;

	after_ant_num = NULL;
	while (list)
	{
		str = (char*)list->content;
		if (ft_isdigit(str[0]) && !ft_strchr(str, ' ') && !ft_strchr(str, '-'))
			after_ant_num = list->next;
		if (lem->flag_q == 0)
			ft_putendl(str);
		list = list->next;
	}
	if (lem->flag_q == 0 && lem->flag_p == 0)
		ft_putchar('\n');
	return (after_ant_num);
}