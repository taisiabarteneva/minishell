/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_child_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 22:12:30 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/24 22:17:02 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_child_exit_status(int *status)
{
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		*status = WTERMSIG(*status) + 128;
	else if (WIFSTOPPED(*status))
		*status = WSTOPSIG(*status);
}

void	wait_child_processes(t_shell **shell, pid_t id)
{
	pid_t	process;
	int		status;
	int		i;

	status = 0;
	i = 0;
	while (i < (*shell)->process_count)
	{
		process = waitpid(-1, &status, 0);
		if (id == process)
		{
			get_child_exit_status(&status);
			(*shell)->exit_status = status;
		}
		i++;
	}
}
