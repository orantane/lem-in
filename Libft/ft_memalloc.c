/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 17:57:14 by orantane          #+#    #+#             */
/*   Updated: 2019/10/24 19:06:44 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*fresh;
	size_t	i;

	i = 0;
	fresh = (char *)malloc(sizeof(char) * size);
	if (fresh == NULL)
		return (NULL);
	while (i < size)
		fresh[i++] = 0;
	return ((void *)fresh);
}
