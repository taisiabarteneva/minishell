/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_redirects_spaces_quotes.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:27:27 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/12 20:39:05 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
------ TO - DO ------
Rework redirection parsing that takes quotes inside filenames into account.
------ TO - DO ------
*/

static void	ft_go_through_redirects(char *str, int i[5])
{
	if (str[(i[0])] && (str[i[0]] == '<' || str[i[0]] == '>'))
		(i[0])++;
	while (str[++(i[0])] && str[i[0]] == ' ')
		;
	while (str[(i[0])] && str[i[0]] != ' ' && str[i[0]] != '>' && str[i[0]] != '<')
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
			ft_go_through_redirects(str, &i[0]);
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

char	*ft_strip_quotes(char *str, int *index, char quote, t_envars *envs)
{
	int		i;
	char	*tmp[3];

	i = *index;
	while (str[++i] && str[i] != quote)
		if (str[i] == '$' && quote != '\'')
			str = ft_replace_path(str, &i, envs);
	if (i - *index > 1)
	{
		tmp[0] = ft_substr(str, 0, *index);
		tmp[1] = ft_substr(str, *index + 1, i - *index - 1);
		tmp[2] = ft_strdup(&str[i + 1]);
		*index = ft_strlen(tmp[0]) + ft_strlen(tmp[1]) - 1;
	}
	else
	{
		tmp[0] = ft_substr(str, 0, *index);
		*index = ft_strlen(tmp[0]) - 1;
		tmp[1] = ft_strdup(&str[i + 1]);
		tmp[2] = NULL;
	}
	tmp[0] = ft_strjoin(tmp[0], tmp[1], 1, 1);
	tmp[0] = ft_strjoin(tmp[0], tmp[2], 1, 1);
	free(str);
	return (tmp[0]);
}

char	*ft_remove_quotes(char *str, t_envars *envs)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\'')
			str = ft_strip_quotes(str, &i, '\'', NULL);
		else if (str[i] == '\"')
			str = ft_strip_quotes(str, &i, '\"', envs);
		else if (str[i] == '$')
			str = ft_replace_path(str, &i, envs);
	}
	return (str);
}
