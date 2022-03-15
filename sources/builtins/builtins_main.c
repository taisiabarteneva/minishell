/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:44:28 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/15 13:36:03 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	built_ins(t_envars **list, t_cmnds *store, t_shell *shell)
{
	if (!store)
		return ;
	else if (ft_strncmp(store->args[0], "pwd", 4) == 0)
		execute_pwd(shell, store);
	else if (ft_strncmp(store->args[0], "env", 4) == 0)
		execute_env(*list, shell, store->args);
	else if (ft_strncmp(store->args[0], "unset", 6) == 0)
		execute_unset(list, &store->args[1], shell);
	else if (ft_strncmp(store->args[0], "exit", 5) == 0)
		execute_exit(shell, store);
	else if (ft_strncmp(store->args[0], "cd", 3) == 0)
		execute_cd(list, store, shell);
	else if (ft_strncmp(store->args[0], "echo", 5) == 0)
		execute_echo(store->args, shell);
	else if (ft_strncmp(store->args[0], "export", 7) == 0)
		execute_export(list, store, shell);
	else
	{
		// EXECVE
	}
}
