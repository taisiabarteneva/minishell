/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_add_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:53:08 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/15 18:12:05 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	ft_print_command_info(t_cmnds *command)
// {
// 	t_list	*args;
// 	int		i;

// 	i = -1;
// 	args = command->args;
// 	printf("COMMAND REDIRECTS:\n");
// 	while (command->redirs && command->redirs[++i])
// 		printf("%d: %s with mode %d\n", i,
// 			command->redirs[i]->filename, command->redirs[i]->mode);
// 	printf("COMMAND ARGUMETS:\n");
// 	i = 0;
// 	while (args)
// 	{
// 		printf("%d: %s\n", i++, (char *)args->content);
// 		args = args->next;
// 	}
// }

static void	ft_remove_quotes_from_command(t_cmnds *command)
{
	t_list	*args;
	int		i;

	i = -1;
	args = command->args;
	while (command->redirs && command->redirs[++i])
		command->redirs[i]->filename
			= ft_remove_quotes(command->redirs[i]->filename, command->envs);
	while (args)
	{
		args->content = ft_remove_quotes(args->content, command->envs);
		args = args->next;
	}
}

static t_cmnds	*ft_command_new(char *str, t_envars *envs)
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
	command->envs = envs;
	ft_get_command_redirects(str, command);
	str = ft_remove_redirects(str);
	str = ft_remove_spaces(str);
	ft_get_command_arguments(str, command);
	ft_remove_quotes_from_command(command);
	free(str);
	return (command);
}

// ft_print_command_info(command);

static void	ft_init_commands(char *str, t_cmnds **commands, t_envars *envs)
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

t_cmnds	**ft_parse_input(char *s, t_envars *envs)
{
	int		num_of_commands;
	t_cmnds	**commands;

	num_of_commands = ft_check_line_part_one(s) * ft_check_line_part_two(s);
	if (!num_of_commands)
	{
		ft_putstr_fd(CMD_ERROR, 2);
		return (NULL);
	}
	commands = (t_cmnds **)malloc(sizeof(t_cmnds *) * (num_of_commands + 1));
	if (!commands)
		fatal_error(MLC_ERROR);
	ft_init_commands(s, commands, envs);
	return (commands);
}
