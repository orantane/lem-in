/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 20:03:15 by orantane          #+#    #+#             */
/*   Updated: 2019/11/02 22:16:46 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	a;

	a = c;
	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == a)
			return ((unsigned char *)s + i);
		i++;
	}
	return (NULL);
}
