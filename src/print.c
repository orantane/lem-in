/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:50:35 by ksalmi            #+#    #+#             */
/*   Updated: 2020/11/11 17:48:39 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_path_array(t_names **arr, int *pass)
{
	int		i;
	int		j;
	int		flow;
	t_names *tmp;

	i = 0;
	j = -1;
	flow = 0;
	while (arr[i] && ++j < ROUNDS && (j == 0 || pass[j] != 0))
	{
		ft_printf("\nRound: %d\n", j + 1);
		while (arr[i] && i < pass[j + 1])
		{
			tmp = arr[i];
			while (tmp)
			{
				ft_printf("%s->", tmp->room->name);
				tmp = tmp->next;
			}
			ft_printf("  |  Path lenght is %d rooms.\n", arr[i]->len);
			i++;
		}
	}
	ft_putchar('\n');
}

/*
** Creates an array of pointers to paths. Each pointer represents an ant.
** So there are as many pointers as there are ants. Uses the pass_value
** function to evaluate the paths for each ant. Returns the allocated
** array to be printed.
*/

t_names	**prepare_output(t_lem *lem, t_names **paths)
{
	t_prep	p;

	p.routes = mallocate_ant_array(lem);
	p.tmp_ants = lem->ants;
	p.tmp_value = copy_value(lem->value);
	p.i = 0;
	while (p.i < lem->ants)
	{
		lem->tmp_i = p.tmp_value[0];
		lem->tmp_j = p.tmp_value[1];
		free(p.tmp_value);
		p.tmp_value = pass_value(p.tmp_ants, paths, lem->tmp_i, lem->tmp_j + 1);
		p.tmp_ants = p.tmp_ants - (p.tmp_value[1] - p.tmp_value[0] + 1);
		p.j = p.tmp_value[0];
		while (p.j <= p.tmp_value[1])
		{
			p.routes[p.i] = paths[p.j];
			p.j++;
			p.i++;
		}
	}
	free(p.tmp_value);
	return (p.routes);
}

/*
** Prints the result in the correct format. Uses the pass_value
** function to dynamically adjust the amount printed per each step.
*/

void	print_output2(t_print *p, t_names **paths, t_lem *lem)
{
	lem->loop = 0;
	lem->tmp_i = lem->value[0];
	lem->tmp_j = lem->value[1];
	if (lem->value)
		free(lem->value);
	lem->value = pass_value(p->tmp_ants, paths, lem->tmp_i, lem->tmp_j + 1);
	p->tmp_ants = p->tmp_ants - (lem->value[1] - lem->value[0] + 1);
	p->print = p->j + (lem->value[1] - lem->value[0] + 1);
	if (p->print > lem->ants)
		p->print = lem->ants;
	p->j = 0;
	while (p->print && p->j < p->print)
	{
		if (p->routes[p->j] != NULL && lem->flag_q == 0)
			ft_printf("L%d-%s ", (p->j + 1), p->routes[p->j]->room->name);
		if (p->routes[p->j] != NULL)
		{
			p->routes[p->j] = p->routes[p->j]->next;
			if (p->routes[p->j] != NULL)
				lem->loop = 1;
		}
		p->j++;
	}
}

void	print_output(t_lem *lem, t_names **paths)
{
	t_print	p;

	p.i = 0;
	p.j = 0;
	lem->loop = 1;
	p.routes = prepare_output(lem, paths);
	p.tmp_ants = lem->ants;
	while (lem->loop)
	{
		print_output2(&p, paths, lem);
		if (lem->flag_q == 0)
			ft_putchar('\n');
		lem->step_count++;
	}
	free(lem->value);
	free(p.routes);
}

t_list	*print_input_data(t_list *list, t_lem *lem)
{
	t_list	*after_ant_num;
	t_list	*tmp;

	tmp = list;
	after_ant_num = NULL;
	while (list)
	{
		lem->tmp_str = (char*)list->content;
		if (ft_isdigit(lem->tmp_str[0]) && !ft_strchr(lem->tmp_str, ' ')
			&& !ft_strchr(lem->tmp_str, '-') && after_ant_num == NULL)
			after_ant_num = list->next;
		if (lem->flag_q == 0)
			ft_putendl(lem->tmp_str);
		list = list->next;
	}
	if (lem->flag_q == 0 && lem->flag_p == 0)
		ft_putchar('\n');
	while (tmp != after_ant_num)
	{
		list = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = list;
	}
	return (after_ant_num);
}
