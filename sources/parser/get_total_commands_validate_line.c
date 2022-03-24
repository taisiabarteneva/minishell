/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_total_commands_validate_line.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:27:27 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/24 19:42:04 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	ft_check_first_command(char *str, int index)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (str[++i] && i < index)
		if (str[i] != ' ')
			j++;
	if (j)
		return (0);
	return (1);
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
		ft_check_quotes(str[i], &inside_s_quote, &inside_d_quote);
		if (!inside_s_quote && !inside_d_quote
			&& (str[i] == '\\' || str[i] == ';'))
			return (0);
		else if (!inside_s_quote && !inside_d_quote && str[i] == '|')
			num_of_commands++;
		if (!inside_s_quote && !inside_d_quote
			&& str[i] == '|' && num_of_commands == 2)
			if (ft_check_first_command(str, i))
				return (0);
	}
	if (!str || inside_s_quote || inside_d_quote)
		return (0);
	return (num_of_commands);
}

int	ft_check_line_part_two(char *str)
{
	int		inside_quotes[2];
	int		i;
	int		j;

	i = -1;
	while (str && str[++i])
	{
		ft_check_quotes(str[i], &inside_quotes[0], &inside_quotes[1]);
		if (!inside_quotes[0] && !inside_quotes[1] && ft_strchr("<>|", str[i]))
		{
			if (str[i + 1] && ((str[i] == '>' && str[i + 1] == '>')
					|| (str[i] == '<' && str[i + 1] == '<')))
				i++;
			while (str[++i] && str[i] == ' ')
				;
			j = i;
			while (str[i] && !ft_strchr(" <>|", str[i]))
				i++;
			if (!(i - j))
				return (0);
		}
	}
	return (1);
}
