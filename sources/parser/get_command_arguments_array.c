/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_information.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:27:27 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/13 13:37:01 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_get_number_of_arguments(char *line)
{
	int	i;
	int	inside_s_quote;
	int	inside_d_quote;
	int	number_of_argumnets;

	i = -1;
	inside_s_quote = 0;
	inside_d_quote = 0;
	number_of_argumnets = 1;
	while (line[++i])
	{
		ft_check_quotes(line[i], &inside_s_quote, &inside_d_quote);
		if (!inside_s_quote && !inside_d_quote
			&& i && line[i] == ' ' && line[i + 1])
			number_of_argumnets++;
	}
	return (number_of_argumnets);
}

static void	ft_get_command_arguments_part_two(t_cmnds *command, int k)
{
	if (!command->args[k - 1])
		fatal_error(MLC_ERROR);
	command->args[k] = NULL;
}

void	ft_get_command_arguments(char *line, t_cmnds *command)
{
	int	i[5];

	ft_memset(i, 0, sizeof(int) * 5);
	i[0] = -1;
	command->args = (char **)malloc(sizeof(char *)
			* (ft_get_number_of_arguments(line) + 1));
	if (!command->args)
		return ;
	while (line[++i[0]])
	{
		ft_check_quotes(line[i[0]], &i[3], &i[4]);
		if (!i[0] && line[i[0]] == ' ' && !i[1]++)
			;
		if (i[0] && !i[3] && !i[4] && line[i[0]] == ' ')
		{
			if (!line[i[0] + 1])
				break ;
			command->args[i[2]++] = ft_substr(line, i[1], i[0] - i[1]);
			if (!command->args[i[2] - 1])
				fatal_error(MLC_ERROR);
			i[1] = i[0] + 1;
		}
	}
	command->args[i[2]++] = ft_substr(line, i[1], i[0] - i[1]);
	ft_get_command_arguments_part_two(command, i[2]);
}
