/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 22:00:30 by ksalmi            #+#    #+#             */
/*   Updated: 2020/10/28 15:57:48 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		print_error(char *str)
{
	printf("%s\n", str);
	exit(0);
}

static int	check_ants(char *str, t_lem *lem)
{
	static int	ants;

	if (!lem->ants && !ants && !ft_strchr(str, ' '))
	{
		if (!ft_isdigit(str[0]))
			print_error("ERROR! Invalid format!");
		lem->ants = ft_atoi(str);
		if (lem->ants == 0)
			print_error("ERROR! No ants!");
		ants = 1;
	}
	return (ants);
}

static int	check_start_command(char *str, char *str_next)
{
	static int	start;

	if (!ft_strcmp(str, "##start") && ft_memcmp(str_next, "#", 1) &&
		!ft_strchr(str_next, '-'))
		start++;
	return (start);
}

static int	check_end_command(char *str, char *str_next)
{
	static int	end;

	if (!ft_strcmp(str, "##end") && ft_memcmp(str_next, "#", 1) &&
		!ft_strchr(str_next, '-'))
		end++;
	return (end);
}

void		check_errors(t_list *list, t_lem *lem)
{
	char	*str;
	int		start;
	int		end;
	int		ants;

	while (list->next)
	{
		str = (char*)list->content;
		if (str[0] == '#' && str[1] != '#')
		{
			if (!ft_strncmp(str, REQUIRED, ft_strlen(REQUIRED)))
				lem->required = ft_atoi(&str[ft_strlen(REQUIRED)]);
			list = list->next;
			continue ;
		}
		ants = check_ants(str, lem);
		start = check_start_command(str, (char*)list->next->content);
		end = check_end_command(str, (char*)list->next->content);
		if (str[0] == 'L' || str[0] == '\0')
			print_error("ERROR");
		list = list->next;
	}
	if (start != 1 || end != 1 || !ants)
		print_error("ERROR! Invalid format!");
}
