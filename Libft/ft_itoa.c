/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:02:06 by orantane          #+#    #+#             */
/*   Updated: 2020/07/30 17:35:43 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*make_string(long long int modulo, char *str, long long int n,
								long long int len)
{
	int				neg;
	long long int	i;

	neg = 1;
	i = len;
	if (n < 0)
	{
		neg = neg * -1;
		n = n * -1;
	}
	while (n >= 1)
	{
		modulo = n % 10;
		str[--i] = modulo + '0';
		n = n / 10;
	}
	if (neg == -1)
		str[0] = '-';
	str[len] = '\0';
	return (str);
}

static int		calculate_malloc(long long int n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = n * -1;
	}
	while (n >= 1)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(long long int n)
{
	char			*str;
	long long int	modulo;
	long long int	len;

	modulo = 0;
	if (n == (-9223372036854775807 - 1))
	{
		str = "-9223372036854775808";
		str = ft_strdup(str);
		return (str);
	}
	if (n == 0)
	{
		str = "0";
		str = ft_strdup(str);
		return (str);
	}
	len = calculate_malloc(n);
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	str = make_string(modulo, str, n, len);
	return (str);
}
