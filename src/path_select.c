/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 18:34:38 by orantane          #+#    #+#             */
/*   Updated: 2020/10/30 21:25:23 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Sorts the paths of one pass in ascending order according to their lengths.
*/

void		pass_sort_paths_len(t_names **arr, int start, int end)
{
	int		i;
	int		j;
	t_names	*tmp;
	t_names	*tmp2;

	i = start;
	while (i < end)
	{
		j = i + 1;
		while (j < end)
		{
			if (arr[j] && arr[j]->len < arr[i]->len)
			{
				tmp = arr[j];
				tmp2 = arr[i];
				arr[i] = tmp;
				arr[j] = tmp2;
				i = start;
				continue ;
			}
			j++;
		}
		i++;
	}
}

static int	*calculate_value(t_value *v, int *steps, t_names **arr)
{
	int	i;

	i = v->start;
	while (i + 1 < v->end && v->tmp_ants > 0 && arr[i] != NULL)
	{
		if ((v->tmp_ants - ((arr[i + 1]->len - arr[i]->len) *
			(i - v->start + 1))) > 0)
			v->tmp_ants = v->tmp_ants - ((arr[i + 1]->len - arr[i]->len)
			* (i - v->start + 1));
		else
			break ;
		i++;
	}
	if (v->tmp_ants > 0)
		v->mod = v->tmp_ants % (i - v->start + 1);
	steps[2] = (v->tmp_ants / (i - v->start + 1)) + arr[i]->len;
	if (v->mod > 0)
	{
		while (v->mod > 0 && v->mod < (i - v->start + 1) && (i - 1) > 0
			&& steps[2] <= arr[i]->len)
			i--;
		steps[2]++;
	}
	steps[1] = i;
	return (steps);
}

/*
** Functions above and below calculate the steps for a given search
** pass with the amount of ants declared in the input. Then saves the
** optimal amount of paths as index values to an integer array. The
** index values refer to the "arr"-array start and end points. Also
** stores the value of the pass into the 3rd position of the integer
** array.
*/

int			*pass_value(int ants, t_names **arr, int start, int end)
{
	t_value v;
	int		*steps;

	v.tmp_ants = ants;
	v.start = start;
	v.mod = 0;
	v.end = end;
	if (!(steps = (int *)malloc(sizeof(int) * 3)))
		print_error(strerror(errno));
	steps[2] = 0;
	steps[0] = start;
	steps = calculate_value(&v, steps, arr);
	return (steps);
}

/*
** This function will only happen in the case that there is a straight link
** from start to end, in which case all the ants will be sent out at the
** same time.
*/

void		straight_to_end(t_lem *lem)
{
	int	i;

	i = -1;
	while (++i < lem->ants)
		ft_printf("L%d-%s ", (i + 1), lem->end->name);
	ft_putchar('\n');
	exit(0);
}

/*
** Goes through all the seach passes and saves the data of the best one
** into an integer array, then returns the array.
*/

int			*path_select(t_lem *lem, int *pass, t_names **arr)
{
	int		*value;
	int		i;
	int		*tmp;

	i = -1;
	value = 0;
	while (pass[++i + 1] > -1)
	{
		if (!arr[pass[i]])
			break ;
		pass_sort_paths_len(arr, pass[i], pass[i + 1]);
		tmp = pass_value(lem->ants, arr, pass[i], pass[i + 1]);
		if (!value)
			value = tmp;
		else if (value[2] > tmp[2])
		{
			free(value);
			value = tmp;
		}
		else if (tmp)
			free(tmp);
	}
	if (arr[pass[i]] && arr[pass[i]]->room == lem->end)
		straight_to_end(lem);
	return (value);
}
