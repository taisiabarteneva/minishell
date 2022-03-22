/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_change_path.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:01:55 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/22 19:12:51 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_get_delta_of_indexes(char *str, int i)
{
	int	j;

	j = 1;
	if (str[i + 1] && ft_isdigit(str[i + 1]))
		j = 2;
	else
		while (str[++i] && !ft_strchr("\'\"$ =*", str[i]))
			j++;
	return (j);
}

static char	*ft_replace_path(char *str, int *index, t_envars *envs)
{
	char	*value;
	int		i;

	i = *index;
	value = NULL;
	i += ft_get_delta_of_indexes(str, i);
	while (!value && envs)
	{
		if (!ft_strncmp(&str[*index + 1], envs->key, i - *index - 1)
			&& (i - *index - 1) == (int)ft_strlen(envs->key))
			value = ft_strdup(envs->value);
		envs = envs->next;
	}
	if (!value && (i - *index - 1))
		value = ft_strdup("");
	else if (!value && !(i - *index - 1))
		value = ft_strdup("$");
	value = ft_strjoin(ft_substr(str, 0, *index), value, 1, 1);
	*index = ft_strlen(value) - 1;
	value = ft_strjoin(value, ft_strdup(&str[i]), 1, 1);
	free(str);
	return (value);
}

static char	*ft_strip_quotes(char *str, int *index, char quote, t_envars *envs)
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
