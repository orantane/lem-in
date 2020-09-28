/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 12:47:59 by orantane          #+#    #+#             */
/*   Updated: 2020/08/21 20:04:13 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*substr;
	unsigned int	end;

	if (!s)
		return (NULL);
	i = 0;
	end = start + len;
	if (!(substr = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (start < end)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
