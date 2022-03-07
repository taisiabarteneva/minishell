/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:44:28 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/07 20:15:08 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void built_ins(char *cmd, t_envars **list, t_cmnds **commands)
{
	// tmp argument
	char	*path;
	char 	*key;
	char	*line;

	key = "LESS";
	path = "/Users/wurrigon/Desktop";
	line = "hey there";
	if (ft_strncmp((const char *)cmd, "pwd", 3) == 0 &&
		ft_strlen(cmd) == ft_strlen("pwd"))
		execute_pwd();
	else if (ft_strncmp((const char *)cmd, "env", 3) == 0 &&
		ft_strlen(cmd) == ft_strlen("env"))
		execute_env(*list);
	else if (ft_strncmp((const char *)cmd, "unset", 5) == 0 &&
		ft_strlen(cmd) == ft_strlen("unset"))
		execute_unset(list, key);
	else if (ft_strncmp((const char *)cmd, "exit", 4) == 0 &&
		ft_strlen(cmd) == ft_strlen("exit"))
		execute_exit();
	else if (ft_strncmp((const char *)cmd, "cd", 2) == 0 &&
		ft_strlen(cmd) == ft_strlen("cd"))
		execute_cd(list, path);
	else if (ft_strncmp((const char *)cmd, "echo", 4) == 0 &&
		ft_strlen(cmd) == ft_strlen("echo"))
		execute_echo(*commands);
}