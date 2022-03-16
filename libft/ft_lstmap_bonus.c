/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:35:06 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/15 18:04:45 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
			void (*del)(void *))
{
	t_list	*first;
	t_list	*elem;

	if (!lst)
		return (NULL);
	first = NULL;
	(void)del;
	while (lst)
	{
		elem = ft_lstnew(f(lst->content));
		if (!elem)
		{
			ft_lstclear(&first);
			return (NULL);
		}
		ft_lstadd_back(&first, elem);
		lst = lst->next;
	}
	return (first);
}
