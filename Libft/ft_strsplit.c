/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:07:30 by orantane          #+#    #+#             */
/*   Updated: 2019/11/02 18:24:18 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		string_count(char c, char const *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			count++;
		}
		while (s[i] == c)
			i++;
	}
	return (count);
}

static	char	**allocate_memory(char c, char const *s, char **fresh)
{
	int		i;
	int		lenght;
	int		o;

	i = 0;
	lenght = 0;
	o = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			lenght++;
			if (s[i] == c || s[i] == '\0')
			{
				if (!(fresh[o++] = (char *)malloc(sizeof(char) * (lenght + 1))))
					return (NULL);
			}
		}
		lenght = 0;
	}
	return (fresh);
}

static	char	**create_strings(char c, char const *s, char **fresh)
{
	int		i;
	int		j;
	int		pos;

	i = 0;
	pos = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
		{
			fresh[pos][j++] = s[i++];
			if (s[i] == c || s[i] == '\0')
			{
				fresh[pos][j] = '\0';
				pos++;
				j = 0;
			}
		}
	}
	return (fresh);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**fresh;
	int		count;

	if (!s)
		return (NULL);
	count = string_count(c, s);
	fresh = (char **)malloc(sizeof(char *) * (count + 1));
	if (!fresh)
		return (NULL);
	fresh[count] = 0;
	fresh = allocate_memory(c, s, fresh);
	if (!fresh)
		return (NULL);
	fresh = create_strings(c, s, fresh);
	return (fresh);
}
