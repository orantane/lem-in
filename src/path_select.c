/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 18:34:38 by orantane          #+#    #+#             */
/*   Updated: 2020/10/19 20:35:30 by ksalmi           ###   ########.fr       */
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

/*
** Places the ants in the paths of a given pass. 
*/

int		*pass_value(int ants, t_names **arr, int start, int end)
{
    int mod;
    int j;
	int	tmp_ants;
	int	*steps;

    
	tmp_ants = ants;
    j = start;
    mod = 0;
    if (!(steps = (int *)malloc(sizeof(int) * 3)))
        return (0); // MALLOC ERROR!!
    steps[0] = start;
	while (j + 1 < end)
	{
		tmp_ants = tmp_ants - ((arr[j + 1]->len - arr[j]->len) * (j - start + 1));
		if (tmp_ants < 1)
			break ;
        j++;
	}
    if (tmp_ants > 0)
	    mod = tmp_ants % (j - start + 1);
	steps[2] = (tmp_ants / (j - start + 1)) + arr[j]->len;
	if (mod > 0)
    {
        // if (steps[2] <= arr[j]->len) // this if clause doesn't work properly
        //     j--;
		steps[2]++;
    }
    steps[1] = j;
	return (steps);
}

int		*path_select(t_lem *lem, int *pass, t_names **arr)
{
	int		*value;
	int		i;
    int     *tmp;

	i = -1;
    value = 0;
	while (pass[++i + 1] > 0)
	{
        pass_sort_paths_len(arr, pass[i], pass[i + 1]);
        if (!arr[pass[i]])
            break ;
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
	return (value);
}