/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_check_and_replace_path.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:27:27 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/12 20:50:23 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_check_quotes(char c, int *inside_s_quote, int *inside_d_quote)
{
	if (!*inside_d_quote && !*inside_s_quote && c == '\'')
		*inside_s_quote = 1;
	else if (!*inside_d_quote && !*inside_s_quote && c == '\"')
		*inside_d_quote = 1;
	else if (!*inside_d_quote && *inside_s_quote && c == '\'')
		*inside_s_quote = 0;
	else if (*inside_d_quote && !*inside_s_quote && c == '\"')
		*inside_d_quote = 0;
}

int	ft_check_line_part_one(char *str)
{
	int		num_of_commands;
	int		inside_s_quote;
	int		inside_d_quote;
	int		i;

	i = -1;
	inside_s_quote = 0;
	inside_d_quote = 0;
	num_of_commands = 1;
	while (str && str[++i])
	{
		if (str[i] == '\\')
			return (0);
		else if (str[i] == ';')
			return (0);
		else if (!inside_s_quote && !inside_d_quote && str[i] == '|')
			num_of_commands++;
		else
			ft_check_quotes(str[i], &inside_s_quote, &inside_d_quote);
	}
	if (!str || inside_s_quote || inside_d_quote)
		return (0);
	return (num_of_commands);
}

int	ft_check_line_part_two(char *str)
{
	int		inside_s_quote;
	int		inside_d_quote;
	int		i;
	int		j;

	i = -1;
	inside_s_quote = 0;
	inside_d_quote = 0;
	while (str && str[++i])
	{
		ft_check_quotes(str[i], &inside_s_quote, &inside_d_quote);
		if (!inside_s_quote && !inside_d_quote && (str[i] == '<' || str[i] == '>' || str[i] == '|'))
		{
			if (str[i + 1] && ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i + 1] == '<')))
				i++;
			while (str[++i] && str[i] == ' ')
				;
			j = i;
			while (str[i] && str[i] != ' ' && str[i] != '<' && str[i] != '>' && str[i] != '|')
				i++;
			if (!(i - j))
				return (0);
		}
	}
	return (1);
}

char	*ft_replace_path(char *str, int *index, t_envars *envs)
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
