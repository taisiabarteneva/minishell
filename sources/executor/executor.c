/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:09:53 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/18 22:17:46 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_command(t_cmnds *command, t_shell **shell, char **envp)
{
	if (is_built_in(command->args->content))
	{
		handle_pipes_redirects(command, *shell);		
		built_ins(&(command->envs), command, *shell, envp);
	}
	else
		execute_bin(command, shell, envp);
}