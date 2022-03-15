/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_commands_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:53:20 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/14 19:16:27 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_free_command_redirects(t_cmnds *command)
{
	int	i;

	i = -1;
	while (command->redirs && command->redirs[++i])
	{
		free(command->redirs[i]->filename);
		free(command->redirs[i]);
	}
	if (command->redirs)
		free(command->redirs);
}

static void	ft_free_command_arguments(t_cmnds *command)
{
	int	i;

	i = -1;
	while (command->args && command->args[++i])
		free(command->args[i]);
	if (command->args)
		free(command->args);
}

void	ft_commands_clear(t_cmnds **commands)
{
	int	i;

	i = -1;
	if (!commands)
		return ;
	while (commands[++i])
	{
		ft_free_command_arguments(commands[i]);
		ft_free_command_redirects(commands[i]);
		free(commands[i]);
	}
	free(commands);
	commands = NULL;
}
