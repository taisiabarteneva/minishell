/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_find_all_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 18:37:00 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/25 13:02:18 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_for_dollarsign(char *str)
{
	int	inside_s_quote;
	int	inside_d_quote;
	int	wildcards;
	int	i;

	i = -1;
	wildcards = 0;
	inside_s_quote = 0;
	inside_d_quote = 0;
	while (str[++i])
	{
		ft_check_quotes(str[i], &inside_s_quote, &inside_d_quote);
		if (!inside_s_quote && str[i] == '$')
			return (1);
		if (!inside_s_quote && !inside_d_quote && str[i] == '*')
			wildcards++;
	}
	if (!wildcards)
		return (1);
	return (0);
}

void	ft_lst_insert_lst(t_list **lst1, t_list *curr, t_list *lst2)
{
	t_list	*copy;

	if (!lst1 || !lst2 || !curr)
		return ;
	copy = lst2;
	while (lst2)
	{
		copy = lst2->next;
		lst2->next = NULL;
		if (curr->next)
			lst2->next = curr->next;
		curr->next = lst2;
		lst2 = copy;
	}
}

static void	ft_lst_del_value_part_two(t_list **copy, t_list **next)
{
	*next = (*copy)->next->next;
	free((*copy)->next->content);
	free((*copy)->next);
	(*copy)->next = *next;
}

void	ft_lst_del_value(t_list **lst, char *value)
{
	t_list	*copy;
	t_list	*next;

	if (!lst || !value)
		return ;
	copy = *lst;
	if (copy && !ft_strncmp(copy->content, value, ft_strlen(copy->content))
		&& ft_strlen(value) == ft_strlen(copy->content))
	{
		*lst = (*lst)->next;
		free(copy->content);
		free(copy);
	}
	else if (copy && copy->next)
	{
		while (copy->next)
		{
			if (!ft_strncmp(copy->next->content, value, ft_strlen(value))
				&& ft_strlen(value) == ft_strlen(copy->next->content))
				break ;
			copy = copy->next;
		}
		ft_lst_del_value_part_two(&copy, &next);
	}
}
