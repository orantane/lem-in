/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orantane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:02:04 by orantane          #+#    #+#             */
/*   Updated: 2019/11/04 19:05:58 by orantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*elem;
	t_list	*start;

	if (!lst)
		return (NULL);
	elem = f(lst);
	lst = lst->next;
	new = ft_lstnew(elem->content, elem->content_size);
	start = new;
	while (lst)
	{
		elem = f(lst);
		if (!(new->next = ft_lstnew(elem->content, elem->content_size)))
			return (NULL);
		lst = lst->next;
		new = new->next;
	}
	return (start);
}
