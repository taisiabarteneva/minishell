/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:44:28 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/22 21:58:50 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_built_in(char *command)
{
	if (ft_strncmp(command, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(command, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(command, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(command, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(command, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(command, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(command, "export", 7) == 0)
		return (1);
	return (0);
}

void	built_ins(t_envars **list, t_cmnds *commands, t_shell **shell, char **envp)
{
	(void)envp;
	if (!commands->args)
		return ;
	if (ft_strncmp(commands->args->content, "pwd", 4) == 0)
		execute_pwd(shell, commands->args, *list);
	else if (ft_strncmp(commands->args->content, "env", 4) == 0)
		execute_env(*list, shell, commands->args);
	else if (ft_strncmp(commands->args->content, "unset", 6) == 0)
		execute_unset(list, commands->args, shell);
	else if (ft_strncmp(commands->args->content, "exit", 5) == 0)
		execute_exit(shell, commands->args);
	else if (ft_strncmp(commands->args->content, "cd", 3) == 0)
		execute_cd(list, commands->args, shell);
	else if (ft_strncmp(commands->args->content, "echo", 5) == 0)
		execute_echo(commands->args, shell);
	else if (ft_strncmp(commands->args->content, "export", 7) == 0)
		execute_export(list, commands->args, shell);
}