/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_add_commands.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:53:08 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/26 15:22:42 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_check_create_files(t_redirs **arr)
{
	int	fd;
	int	i;

	i = -1;
	while (arr[++i])
	{
		if (arr[i]->mode == 0)
			fd = open(arr[i]->filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		else if (arr[i]->mode == 1)
			fd = open(arr[i]->filename, O_RDONLY, 0777);
		else if (arr[i]->mode == 2)
			fd = open(arr[i]->filename, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if ((arr[i]->mode == 0 || arr[i]->mode == 2) && fd == -1)
			fatal_error("minishell: couldn't open file\n");
		else if (arr[i]->mode == 1 && fd == -1)
		{
			printf("minishell: %s: No such file or directory\n",
				arr[i]->filename);
			return (1);
		}
		close(fd);
	}
	return (0);
}

static t_cmnds	*ft_command_new_part_two(t_cmnds **command)
{
	int		i;

	i = -1;
	while ((*command)->redirs && (*command)->redirs[++i])
		(*command)->redirs[i]->filename
			= ft_remove_quotes((*command)->redirs[i]->filename, *command);
	ft_replace_wildcards(*command, (*command)->args);
	if (ft_check_create_files((*command)->redirs))
	{
		(*command)->shell->exit_status = 1;
		ft_free_command_redirects(*command);
		ft_lstclear(&(*command)->args);
		free(*command);
		*command = NULL;
	}
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
	if (str && str[0] && str[1])
		ft_get_command_arguments(str, command);
	else
		command->args = NULL;
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

	num_of_commands = ft_check_line_part_one(s)
		* ft_check_line_part_two(s) * ft_check_line_part_three(s);
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
