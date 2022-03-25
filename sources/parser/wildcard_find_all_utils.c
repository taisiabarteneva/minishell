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

char	**ft_init_wildcard_pieces(char *str)
{
	int		i[4];
	char	**pieces;

	ft_memset(i, 0, sizeof(int) * 4);
	i[0] = -1;
	i[1] = 1;
	pieces = NULL;
	while (str[++i[0]])
	{
		ft_check_quotes(str[i[0]], &i[2], &i[3]);
		if (!i[2] && !i[3] && str[i[0]] == '*')
			i[1]++;
	}
	pieces = (char **)malloc(sizeof(char *) * (i[1] + 1));
	if (!pieces)
		return (NULL);
	return (pieces);
}

void	ft_get_wildcard_pieces(char *str, char **pieces)
{	
	int	i[5];

	ft_memset(i, 0, sizeof(int) * 5);
	i[0] = -1;
	while (str[++i[0]])
	{
		ft_check_quotes(str[i[0]], &i[3], &i[4]);
		while (i[3] || i[4])
		{
			i[0]++;
			ft_check_quotes(str[i[0]], &i[3], &i[4]);
		}
		if (str[i[0]] == '*')
		{
			if (i[0] && str[i[0] - 1] == '*')
				i[1]++;
			else
			{
				pieces[i[2]++] = ft_substr(str, i[1], i[0] - i[1]);
				i[1] = i[0] + 1;
			}
		}
	}
	pieces[i[2]++] = ft_substr(str, i[1], i[0]);
	pieces[i[2]] = NULL;
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
