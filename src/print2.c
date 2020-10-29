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
		ft_printf("\nRound: %d, paths found: %d\n", j, pass[j + 1] - pass[j]);
		while (arr[i] && i < pass[j + 1])
		{
			tmp = arr[i];
			while (tmp)
			{
				ft_printf("%s->", tmp->room->name);
				tmp = tmp->next;
			}
			ft_printf("  |  The path length is %d.\n", arr[i]->len);
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

static t_names	**prepare_ant_array(t_lem *lem)
{
	t_names	**routes;

	if (!(routes = (t_names**)malloc(sizeof(t_names *) * (lem->ants + 1))))
			print_error(strerror(errno));
	routes[lem->ants] = NULL;
	return (routes);
}

static int	*copy_value(int *value)
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

t_names		**prepare_output(t_lem *lem, t_names **paths)
{
	t_prep	p;

	p.routes = prepare_ant_array(lem);
	p.i = -1;
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

/*t_names		**prepare_output(t_lem *lem, t_names **paths)
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
}*/

/*
** Prints the result in the correct format. Uses the pass_value
** function to dynamically adjust the amount printed per each
** step.
*/

/*static void	print_output2(t_print *p, t_names **paths, t_lem *lem)
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