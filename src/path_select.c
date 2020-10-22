/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 18:34:38 by orantane          #+#    #+#             */
/*   Updated: 2020/10/22 16:33:04 by orantane         ###   ########.fr       */
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
		print_error(strerror(errno));
    steps[2] = 0;
    steps[0] = start;
	while (j + 1 < end && tmp_ants > 0)
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
        while (mod < (j - start + 1) && (j - 1) > 0 && steps[2] <= arr[j]->len)
        {
            j--;
            steps[2] = (tmp_ants / (j - start + 1)) + arr[j]->len;
        }
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
	return (value);
}