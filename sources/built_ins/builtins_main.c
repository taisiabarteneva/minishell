/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:44:28 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/12 23:18:21 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	built_ins(t_envars **list, t_cmnds *store, t_shell *shell)
{
	if (ft_strncmp(store->args[0], "pwd", 4) == 0)
		execute_pwd(shell, store);
	else if (ft_strncmp((const char *)store->args[0], "env", 4) == 0)
		execute_env(*list, shell);
	else if (ft_strncmp((const char *)store->args[0], "unset", 6) == 0)
		execute_unset(list, &store->args[1], shell);
	else if (ft_strncmp((const char *)store->args[0], "exit", 5) == 0)
		execute_exit(shell, store);
	else if (ft_strncmp((const char *)store->args[0], "cd", 3) == 0)
		execute_cd(list, store, shell);
	else if (ft_strncmp((const char *)store->args[0], "echo", 5) == 0)
		execute_echo(store, shell);
	else if (ft_strncmp((const char *)store->args[0], "export", 7) == 0)
		execute_export(list, store, shell);
	else
	{
		// EXECVE
	}
}
