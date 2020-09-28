/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 07:59:33 by orantane          #+#    #+#             */
/*   Updated: 2019/11/07 01:35:02 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char const *s1, int fd)
{
	int i;

	if (!s1 || !fd)
		return ;
	i = 0;
	while (s1[i] != '\0')
	{
		ft_putchar_fd(s1[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}
