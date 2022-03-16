/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:09:53 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/16 22:30:54 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_command(t_cmnds *command, t_shell *shell, char **envp)
{
	if (is_built_in(command->args->content))
		built_ins(&(command->envs), command, shell, envp);
	else
		execute_bin(command, shell, envp);
}