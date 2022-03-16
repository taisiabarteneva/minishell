/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_redirects_spaces.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:27:27 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/13 16:07:09 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_go_through_redirects(char *str, int i[5])
{
	if (str[(i[0])] && (str[i[0]] == '<' || str[i[0]] == '>'))
		(i[0])++;
	while (str[++(i[0])] && str[i[0]] == ' ')
		;
	while (str[(i[0])] && str[i[0]] != ' '
		&& str[i[0]] != '>' && str[i[0]] != '<')
	{
		ft_check_quotes(str[i[0]], &i[3], &i[4]);
		if (i[3] || i[4])
		{
			while (i[3] || i[4])
			{
				i[0]++;
				ft_check_quotes(str[i[0]], &i[3], &i[4]);
			}
		}
		i[0]++;
	}
}

char	*ft_remove_redirects(char *str)
{
	char	*tmp;
	int		i[5];

	ft_memset(&i, 0, sizeof(int) * 5);
	tmp = NULL;
	while (str[i[0]])
	{
		ft_check_quotes(str[i[0]], &i[3], &i[4]);
		if (!i[3] && !i[4] && (str[i[0]] == '<' || str[i[0]] == '>'))
		{
			tmp = ft_substr(str, 0, i[0]);
			i[1] = i[0];
			ft_go_through_redirects(str, i);
			tmp = ft_strjoin(tmp, ft_strdup(&str[i[0]]), 1, 1);
			free(str);
			i[0] = i[1];
			str = tmp;
			i[0]--;
		}
		i[0]++;
	}
	if (!tmp)
		return (str);
	return (tmp);
}

char	*ft_remove_spaces(char *str)
{
	char	*tmp;
	int		i[5];

	ft_memset(&i, 0, sizeof(int) * 5);
	tmp = NULL;
	while (str[i[0]])
	{
		ft_check_quotes(str[i[0]], &i[4], &i[3]);
		if (!i[3] && !i[4] && str[i[0]] == ' ')
		{
			tmp = ft_substr(str, 0, i[0] + 1);
			i[1] = i[0];
			while (str[++i[0]] && str[i[0]] == ' ')
				;
			tmp = ft_strjoin(tmp, ft_strdup(&str[i[0]]), 1, 1);
			free(str);
			i[0] = i[1];
			str = tmp;
		}
		i[0]++;
	}
	if (!tmp)
		return (str);
	return (tmp);
}
