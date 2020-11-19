/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:08:26 by orantane          #+#    #+#             */
/*   Updated: 2020/11/11 18:39:35 by ksalmi           ###   ########.fr       */
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

	ft_memset(lem, 0, sizeof(t_lem));
	if (!(lem->hash_t = (t_names**)malloc(sizeof(t_names*) * HASH_SIZE)))
		print_error(strerror(errno));
	init_arr_null(HASH_SIZE, lem->hash_t);
	if (!(lem->pass = (int*)malloc(sizeof(int) * ROUNDS + 1)))
		print_error(strerror(errno));
	i = -1;
	while (++i < ROUNDS)
		lem->pass[i] = -1;
	lem->pass[0] = 0;
}

void	init_lem_again(t_lem *lem)
{
	lem->read = NULL;
	lem->que = NULL;
	lem->r = 1;
	lem->max = lem->s_bneck * MAX_PATHS;
	if (!(lem->arr = (t_names **)malloc(sizeof(t_names *) * lem->max + 1)))
		print_error(strerror(errno));
	init_arr_null(lem->max, lem->arr);
}

t_names	*free_names_node_return_next(t_names *to_free, t_names *tmp)
{
	tmp = to_free->next;
	free(to_free);
	return (tmp);
}
