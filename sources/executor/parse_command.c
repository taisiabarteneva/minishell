/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 22:15:34 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/24 22:49:54 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**parse_paths(t_envars *list)
{
	char	**my_paths;	
	char	*path_env;
	int		i;

	i = 0;
	path_env = find_env_node(list, "PATH");
	if (!path_env)
		return (NULL);
	my_paths = ft_split(path_env, ':');
	if (!my_paths)
		fatal_error(MLC_ERROR);
	while (my_paths[i])
	{
		my_paths[i] = ft_strjoin(my_paths[i], "/", 0, 0);
		if (!my_paths[i])
			fatal_error(MLC_ERROR);
		i++;
	}
	return (my_paths);
}

void	handle_no_path(char **path, char ***cmd_args)
{
	*path = ft_strjoin("/", (*cmd_args)[0], 0, 0);
	if (!*path)
		fatal_error(MLC_ERROR);
	if (access(*path, F_OK))
		*path = NULL;
}

void	exec_system_bin(t_cmnds *command, char **path, char ***cmd_args)
{
	char	**paths;
	int		i;

	i = 0;
	paths = parse_paths(command->envs);
	*cmd_args = get_command_arguments(command->args);
	if (!(*cmd_args))
		fatal_error(MLC_ERROR);
	while (paths && paths[i])
	{
		*path = ft_strjoin(paths[i], (*cmd_args)[0], 0, 0);
		if (!*path)
			fatal_error(MLC_ERROR);
		if (access(*path, F_OK) == 0)
			break ;
		free(paths[i]);
		free(*path);
		*path = NULL;
		i++;
	}
	if (!*path)
		handle_no_path(path, cmd_args);
	free(paths);
}

void	exec_non_system_bin(t_cmnds *command, char **path, char ***cmdargs)
{
	*cmdargs = get_command_arguments(command->args);
	if (!*cmdargs)
		fatal_error(MLC_ERROR);
	*path = (*cmdargs)[0];
}
