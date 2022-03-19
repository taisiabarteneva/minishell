/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:09:53 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/19 18:50:07 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_command(t_cmnds *command, t_shell **shell, char **envp)
{
	int lol;
	if (is_built_in(command->args->content))
	{
		lol = handle_pipes_redirects(command, *shell);		
		built_ins(&(command->envs), command, *shell, envp);
		dup2(lol, STDOUT_FILENO);
	}
	else
		execute_bin(command, shell, envp);
}