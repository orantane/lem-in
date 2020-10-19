/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <oskari.rantanen@student.hive.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 18:34:38 by orantane          #+#    #+#             */
/*   Updated: 2020/10/19 14:55:38 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Sorts the paths of one pass in ascending order according to their lengths.
*/
void    pass_sort_paths_len(t_names **arr, int start, int end)
{
    int     i;
    int     j;
    t_names *tmp;
    t_names *tmp2;

    i = start;
    while (i < end)
    {
        j = i + 1;
        while (j < end)
        {
            if (arr[j]->len < arr[i]->len)
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

/*
int		max_flow_pass(int *pass, int i)
{
	int		flow;

    flow = 0;
	if (pass[i + 1] > pass[i])
        flow = pass[i + 1] - pass[i];
	return (flow);
}
*/
int		pass_value(int ants, t_names **arr, int start, int end)
{
    int mod;
    int j;
	int	tmp_ants;
	int	steps;

    
	tmp_ants = ants;
    j = start;
    mod = 0;
	while (j + 1 < end)
	{
		tmp_ants = tmp_ants - ((arr[j + 1]->len - arr[j]->len) * (j - start + 1));
		if (tmp_ants < 1)
			break ;
        j++;
	}
    if (tmp_ants > 0)
	    mod = tmp_ants % (j - start + 1);
	steps = (tmp_ants / (j - start + 1)) + arr[j]->len;
	if (mod > 0)
		steps++;
	return (steps);
}

int		path_select(t_lem *lem, int *pass, t_names **arr)
{
	int		value;
	int		i;
	int		ants;
	int		j;
 //   int     best_value;//save best value
//    int     best_j; //save best ending point --- from pass value function
//    int     best_start;//save best starting point

	i = -1;
	j = 0;
	ants = 0;
	while (pass[++i + 1] > 0)
	{
        pass_sort_paths_len(arr, pass[i], pass[i + 1]);
		value = pass_value(lem->ants, arr, pass[i], pass[i + 1]);
        ft_printf("value:%d\n", value);
	}
	return (j);
}