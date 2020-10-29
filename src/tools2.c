/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:08:26 by orantane          #+#    #+#             */
/*   Updated: 2020/10/29 21:48:35 by ksalmi           ###   ########.fr       */
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
	int	i;

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
	lem->required = 0;
	lem->flag_q = 0;
	lem->flag_p = 0;
	lem->step_count = 0;
	if (!(lem->pass = (int*)malloc(sizeof(int) * ROUNDS + 1)))
		print_error(strerror(errno));
	i = -1;
	while (++i < ROUNDS)
		lem->pass[i] = -1;
	lem->pass[0] = 0;
}

void	init_lem_again(t_lem *lem)
{
	lem->r = 1;
	lem->max = lem->s_bneck * MAX_PATHS;
	if (!(lem->arr = (t_names **)malloc(sizeof(t_names *) * lem->max + 1)))
		print_error(strerror(errno));
	init_arr_null(lem->max, lem->arr);
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

t_names	*free_names_node_return_next(t_names *to_free, t_names *tmp)
{
	tmp = to_free->next;
	free(to_free);
	return (tmp);
}

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