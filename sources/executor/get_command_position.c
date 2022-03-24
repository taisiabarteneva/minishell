/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_position.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 22:24:22 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/24 22:25:20 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_first_command(t_cmnds *command, t_shell **shell, int in)
{
	dup2((*shell)->pipes[0][1], STDOUT_FILENO);
	handle_pipes_redirects(command, shell, in);
	close((*shell)->pipes[0][0]);
}

void	handle_last_command(t_cmnds *command, t_shell **shell, int in)
{
	handle_pipes_redirects(command, shell, in);
	dup2((*shell)->pipes[(*shell)->process_count - 2][0], STDIN_FILENO);
	close((*shell)->pipes[(*shell)->process_count - 2][1]);
}

void	handle_standard_command(t_shell **shell, int cmd_pos)
{
	dup2((*shell)->pipes[cmd_pos - 1][0], STDIN_FILENO);
	dup2((*shell)->pipes[cmd_pos][1], STDOUT_FILENO);
}

void	get_command_position(t_cmnds *command, t_shell **shell, int cmd_pos,
			int in)
{
	if (cmd_pos == 0)
		handle_first_command(command, shell, in);
	else if (cmd_pos == (*shell)->process_count - 1)
		handle_last_command(command, shell, in);
	else
		handle_standard_command(shell, cmd_pos);
}
