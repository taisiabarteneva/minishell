/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_add_or_clear_commands.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:53:08 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/12 20:59:45 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmnds	**ft_parse_input(char *s, t_envars *envs)
{
	int		num_of_commands;
	t_cmnds	**commands;

	num_of_commands = ft_check_line_part_one(s) * ft_check_line_part_two(s);
	if (!num_of_commands)
		fatal_error(CMD_ERROR);
	commands = (t_cmnds **)malloc(sizeof(t_cmnds *) * (num_of_commands + 1));
	if (!commands)
		fatal_error(MLC_ERROR);
	ft_init_commands(s, commands, envs);
	return (commands);
}

void	ft_init_commands(char *str, t_cmnds **commands, t_envars *envs)
{
	int	i[5];

	ft_memset(i, 0, sizeof(int) * 5);
	i[0] = -1;
	while (str[++i[0]])
	{
		ft_check_quotes(str[i[0]], &i[3], &i[4]);
		if (!i[3] && !i[4] && str[i[0]] == '|')
		{
			commands[i[2]++] = ft_command_new(ft_substr(str,
						i[1], i[0] - i[1]), envs);
			if (!commands[i[2] - 1])
				fatal_error(MLC_ERROR);
			i[1] = i[0] + 1;
		}
	}
	commands[i[2]++] = ft_command_new(ft_substr(str, i[1], i[0] - i[1]), envs);
	if (!commands[i[2] - 1])
		fatal_error(MLC_ERROR);
	commands[i[2]] = NULL;
}

t_cmnds	*ft_command_new(char *str, t_envars *envs)
{
	t_cmnds	*command;
	int		i;

	if (!str)
		return (NULL);
	command = (t_cmnds *)malloc(sizeof(t_cmnds));
	if (!command)
		return (NULL);
	i = -1;
	ft_memset(command, 0, sizeof(t_cmnds));
	ft_get_command_infile(str, command);
	ft_get_command_outfile(str, command);
	str = ft_remove_redirects(str);
	str = ft_remove_spaces(str);
	ft_get_command_arguments(str, command);
	// while (command->args && command->args[++i])
	// 	printf("%s-\n", command->args[i]);
	command->envs = envs;
	free(str);
	return (command);
}

void	ft_commands_clear(t_cmnds **commands)
{
	int	i;
	int	k;

	i = -1;
	if (!commands)
		return ;
	while (commands[++i])
	{
		if (commands[i]->outfile)
			free(commands[i]->outfile);
		if (commands[i]->infile)
			free(commands[i]->infile);
		k = -1;
		while (commands[i]->args && commands[i]->args[++k])
			free(commands[i]->args[k]);
		if (commands[i]->args)
			free(commands[i]->args);
		if (commands[i])
			free(commands[i]);
	}
	free(commands);
	commands = NULL;
}
