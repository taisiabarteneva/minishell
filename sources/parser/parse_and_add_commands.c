/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_add_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:53:08 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/25 18:44:10 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmnds	*ft_command_new_part_two(t_cmnds **command)
{
	int		i;

	i = -1;
	while ((*command)->redirs && (*command)->redirs[++i])
		(*command)->redirs[i]->filename
			= ft_remove_quotes((*command)->redirs[i]->filename, *command);
	ft_replace_wildcards(*command, (*command)->args);
	return (*command);
}

static t_cmnds	*ft_command_new(char *str, t_envars *envs, t_shell *shell)
{
	t_cmnds	*command;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	command = (t_cmnds *)malloc(sizeof(t_cmnds));
	if (!command)
		return (NULL);
	i = -1;
	j = -1;
	ft_memset(command, 0, sizeof(t_cmnds));
	command->envs = envs;
	command->shell = shell;
	ft_get_command_redirects(str, command);
	str = ft_remove_redirects(str);
	str = ft_remove_spaces(str);
	ft_get_command_arguments(str, command);
	command = ft_command_new_part_two(&command);
	free(str);
	return (command);
}

static int	ft_init_commands(char *str, t_cmnds **commands,
	t_envars *envs, t_shell *shell)
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
						i[1], i[0] - i[1]), envs, shell);
			if (!commands[i[2] - 1])
				return (1);
			i[1] = i[0] + 1;
		}
	}
	commands[i[2]++] = ft_command_new(ft_substr(str, i[1], i[0] - i[1]),
			envs, shell);
	if (!commands[i[2] - 1])
		return (1);
	commands[i[2]] = NULL;
	return (0);
}

t_cmnds	**ft_parse_input(char *s, t_envars *envs, t_shell *shell)
{
	int		num_of_commands;
	t_cmnds	**commands;

	num_of_commands = ft_check_line_part_one(s) * ft_check_line_part_two(s);
	if (!num_of_commands)
	{
		ft_putstr_fd(CMD_ERROR, 2);
		shell->exit_status = 2;
		return (NULL);
	}
	commands = (t_cmnds **)malloc(sizeof(t_cmnds *) * (num_of_commands + 1));
	if (!commands)
		fatal_error(MLC_ERROR);
	if (ft_init_commands(s, commands, envs, shell))
		ft_commands_clear(&commands);
	return (commands);
}
