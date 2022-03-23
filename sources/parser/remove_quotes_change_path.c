/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_change_path.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:01:55 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/22 20:29:25 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_get_delta_of_indexes(char *str, int i,
	char **value, t_cmnds *command)
{
	int	j;

	j = 1;
	if (str[i + 1] && ft_isdigit(str[i + 1]))
		j = 2;
	else if (str[i + 1] && str[i + 1] == '?')
	{
		if (command && command->shell)
				*value = ft_itoa(command->shell->exit_status);
		j = 2;
	}
	else
		while (str[++i] && !ft_strchr("\'\"$ =*", str[i]))
			j++;
	return (j);
}

static char	*ft_replace_path(char *str, int *index, t_cmnds *command)
{
	char		*value;
	t_envars	*env;
	int			i;

	i = *index;
	value = NULL;
	env = command->envs;
	i += ft_get_delta_of_indexes(str, i, &value, command);
	while (!value && env)
	{
		if (!ft_strncmp(&str[*index + 1], env->key, i - *index - 1)
			&& (i - *index - 1) == (int)ft_strlen(env->key))
			value = ft_strdup(env->value);
		env = env->next;
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

static char	*ft_strip_quotes(char *str, int *index,
	char quote, t_cmnds *command)
{
	int		i;
	char	*tmp[3];

	i = *index;
	while (str[++i] && str[i] != quote)
		if (str[i] == '$' && quote != '\'')
			str = ft_replace_path(str, &i, command);
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

char	*ft_remove_quotes(char *str, t_cmnds *command)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '\'')
			str = ft_strip_quotes(str, &i, '\'', command);
		else if (str[i] == '\"')
			str = ft_strip_quotes(str, &i, '\"', command);
		else if (str[i] == '$')
			str = ft_replace_path(str, &i, command);
	}
	return (str);
}
