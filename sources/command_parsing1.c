/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:27:27 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/07 18:47:33 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_check_line(char *str)
{
	int		inside_s_quote;
	int		inside_d_quote;
	int		i;

	i = -1;
	inside_s_quote = 0;
	inside_d_quote = 0;
	while (str && str[++i])
	{
		if (str[i] == '\\')
			return (EXIT_FAILURE);
		else if (str[i] == ';')
			return (EXIT_FAILURE);
		else if (!inside_d_quote && !inside_s_quote && str[i] == '\'')
			inside_s_quote = 1;
		else if (!inside_d_quote && !inside_s_quote && str[i] == '\"')
			inside_d_quote = 1;
		else if (!inside_d_quote && inside_s_quote && str[i] == '\'')
			inside_s_quote = 0;
		else if (inside_d_quote && !inside_s_quote && str[i] == '\"')
			inside_d_quote = 0;
	}
	if (!str || inside_d_quote || inside_s_quote)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static char	*ft_replace_path(char *str, int *index, t_envars *envs)
{
	char	*value;
	int		i;

	i = *index;
	value = NULL;
	while (str[++i] && str[i] != '\'' && str[i] != '\"'
		&& str[i] != '$' && str[i] != ' ')
		;
	while (!value && envs)
	{
		if (!ft_strncmp(&str[*index + 1], envs->key, i - *index - 1))
			value = ft_strdup(envs->value);
		envs = envs->next;
	}
	if (value)
	{
		value = ft_strjoin(ft_substr(str, 0, *index), value, 1, 1);
		*index = ft_strlen(value) - 1;
		value = ft_strjoin(value, ft_strdup(&str[i]), 1, 1);
		free(str);
		return (value);
	}
	free(str);
	return (ft_strdup(""));
}

static char	*ft_pre_parsing(char *str, int *index, char quote, t_envars *envs)
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

static char	*ft_remove_spaces(char *str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
		{
			j = 0;
			while (str[++i] && str[i] == ' ')
				j++;
		}
	}
}

t_cmnds	*ft_parse_input(char *s, t_envars *envs)
{
	int		i;
	char	*str;
	t_cmnds	*commands;

	if (ft_check_line(s))
		fatal_error(CMD_ERROR);
	i = -1;
	str = ft_strdup(s);
	while (str && str[++i])
	{
		if (str[i] == '\'')
			str = ft_pre_parsing(str, &i, '\'', NULL);
		else if (str[i] == '\"')
			str = ft_pre_parsing(str, &i, '\"', envs);
		else if (str[i] == '$')
			str = ft_replace_path(str, &i, envs);
	}
	// commands = ft_parse_commands(str);
	ft_putendl_fd(str, 1);
	free(str);
	// if (!commands)
		// fatal_error(MLC_ERROR);
	return (NULL);
}
