/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 08:36:30 by orantane          #+#    #+#             */
/*   Updated: 2020/07/30 17:38:11 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_zero(long long int i, const char *str)
{
	if ((i - 2) < 0)
		return (0);
	if ((str[i] > 47 && str[i] < 58 && str[i - 1] == 43 && str[i - 2] == 43) ||
		(str[i] > 47 && str[i] < 58 && str[i - 1] == 45 && str[i - 2] == 43))
		return (1);
	return (0);
}

long long int	ft_atoi(const char *str)
{
	long long int r;
	long long int s;
	long long int i;

	r = 0;
	s = 1;
	i = 0;
	while (str[i] == '+' || str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		s = -1;
		i++;
	}
	if ((check_zero(i, str)))
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] < 48 || str[i] > 57)
			return (s * r + '\0');
		else
			r = r * 10 + str[i++] - '0';
	}
	return (s * r);
}
