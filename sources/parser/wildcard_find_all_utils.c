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
