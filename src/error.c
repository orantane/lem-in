/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksalmi <ksalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 22:00:30 by ksalmi            #+#    #+#             */
/*   Updated: 2020/11/11 19:17:23 by ksalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Displays the error message sent to the function and exits the program.
*/

void		print_error(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
}

static int	check_ants(char *str, t_lem *lem)
{
	static int	ants;
	char		*tmp;

	if (!lem->ants && !ants && !ft_strchr(str, ' '))
	{
		if (!ft_isdigit(str[0]))
			print_error("ERROR! Invalid format.");
		lem->ants = ft_atoi(str);
		tmp = ft_itoa(lem->ants);
		if (lem->ants < 1 || ft_strcmp(tmp, str) != 0)
			print_error("ERROR! Invalid amount of ants.");
		if (tmp)
			free(tmp);
		ants = 1;
	}
	return (ants);
}

static int	check_start_command(char *str, char *str_next)
{
	static int	start;
	static int	number_of_starts;

	if (!ft_strcmp(str, "##start"))
		number_of_starts++;
	if (!ft_strcmp(str, "##start") && ft_memcmp(str_next, "#", 1) &&
		!ft_strchr(str_next, '-'))
		start++;
	if (number_of_starts > 1)
		print_error("ERROR! Invalid format.");
	return (start);
}

static int	check_end_command(char *str, char *str_next)
{
	static int	end;
	static int	number_of_ends;

	if (!ft_strcmp(str, "##end"))
		number_of_ends++;
	if (!ft_strcmp(str, "##end") && ft_memcmp(str_next, "#", 1) &&
		!ft_strchr(str_next, '-'))
		end++;
	if (number_of_ends > 1)
		print_error("ERROR! Invalid format.");
	return (end);
}

/*
** Checks the info saved into the linked list for possible errors. These
** errors include the wrong number of ##start and ##end rooms, a valid
** amount of ants, and room names that start with an 'L'. There can also
** be no empty lines in the input data.
*/

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
			print_error("ERROR! Invalid format.");
		list = list->next;
	}
	if (start != 1 || end != 1 || !ants)
		print_error("ERROR! Invalid format.");
}
