/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <orantane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 02:26:01 by orantane          #+#    #+#             */
/*   Updated: 2020/08/20 23:50:37 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_copy(char **line, const int fd, char **strings, int done)
{
	int		i;
	char	*rest;

	i = 0;
	while (strings[fd][i] != '\n' && strings[fd][i] != '\0')
		i++;
	if (strings[fd][i] == '\n')
	{
		*line = ft_strsub(strings[fd], 0, i);
		rest = ft_strdup(&strings[fd][i + 1]);
		free(strings[fd]);
		strings[fd] = rest;
		if (strings[fd][0] == '\0')
			ft_strdel(&strings[fd]);
	}
	else
	{
		*line = ft_strdup(strings[fd]);
		ft_strdel(&strings[fd]);
		done = 1;
		return (0);
	}
	return (1);
}

static int	checkout(char **line, const int fd, char **strings, int ret)
{
	static int	done;

	if (!done)
		done = 0;
	if (done == 1)
	{
		done = 0;
		return (0);
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0 && strings[fd] == NULL)
		return (0);
	else
		return (ft_copy(line, fd, strings, done));
}

int			get_next_line(const int fd, char **line, int end)
{
	char		buff[BUFF_SIZE + 1];
	static char	*strings[FD_SIZE];
	char		*temp;
	int			ret;
	int			stop;

	stop = 0;
	if (fd < 0 || !line || fd > FD_SIZE)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (strings[fd] == NULL)
			strings[fd] = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(strings[fd], buff);
			free(strings[fd]);
			strings[fd] = temp;
		}
		if ((ft_strchr(strings[fd], '\n')) || (end > 0 && ++stop == end))
			break ;
	}
	return (checkout(line, fd, strings, ret));
}
