/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:28:55 by orantane          #+#    #+#             */
/*   Updated: 2020/11/11 19:10:46 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*coordinate_check(char *line, t_room *new)
{
	char	*s;
	int		i;
	int		space;

	s = ft_strchr(line, ' ');
	if (!s)
		print_error("ERROR! Invalid or missing coordinates");
	s = s + 1;
	i = 0;
	space = 0;
	while (s[i] && (ft_isdigit(s[i]) || s[i] == ' '))
	{
		if (s[i] == ' ')
			space++;
		i++;
	}
	if (s[i] || space != 1)
		print_error("ERROR! Invalid or missing coordinates");
	new->x = ft_atoi(s);
	new->y = ft_atoi(ft_strchr(s, ' '));
	return (new);
}

t_names	**mallocate_ant_array(t_lem *lem)
{
	t_names	**routes;

	if (!(routes = (t_names**)malloc(sizeof(t_names *) * (lem->ants + 1))))
		print_error(strerror(errno));
	routes[lem->ants] = NULL;
	return (routes);
}

int		*copy_value(int *value)
{
	int	*new;
	int	i;

	if (!(new = (int *)malloc(sizeof(int) * 3)))
		print_error(strerror(errno));
	i = 0;
	while (i < 3)
	{
		new[i] = value[i];
		i++;
	}
	return (new);
}

/*
** Checks if there were any flags used, saves the ones used.
*/

void	check_flags(t_lem *lem, char *flag_str)
{
	int	i;

	i = -1;
	while (flag_str[++i])
	{
		if (flag_str[i] == 'q')
			lem->flag_q = 1;
		if (flag_str[i] == 'p')
			lem->flag_p = 1;
		if (flag_str[i] == 'r')
			lem->flag_r = 1;
		if (flag_str[i] == 'l')
			lem->flag_l = 1;
		if (flag_str[i] == 'h')
			lem->flag_h = 1;
	}
}

void	check_link_format(char *str)
{
	int i;

	i = 0;
	if (str[0] == '#')
		return ;
	if (!ft_strchr(str, '-'))
		print_error("ERROR! Invalid or missing link.");
	while (str[i] && str[i] != '-')
		i++;
	if (i == 0 || str[i + 1] == '\0')
		print_error("ERROR! Invalid link format.");
	if (ft_strchr(str + (i + 1), '-'))
		print_error("ERROR! Link has multiple '-' characters.");
}
