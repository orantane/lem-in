/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:24:42 by orantane          #+#    #+#             */
/*   Updated: 2019/10/23 16:58:58 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*a;

	if (len == 0)
		return (b);
	a = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		*(a++) = (unsigned char)c;
		i++;
	}
	return (b);
}
