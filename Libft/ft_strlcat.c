/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 08:15:09 by orantane          #+#    #+#             */
/*   Updated: 2019/11/04 13:10:27 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	result;

	i = ft_strlen(dest);
	result = ft_strlen(src);
	j = 0;
	if (size == 0)
		return (result);
	if (size < i)
		result = result + size;
	else
		result = result + i;
	while (src[j] != '\0' && i < size - 1 && dest != src)
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (result);
}
