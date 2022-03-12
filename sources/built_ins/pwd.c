/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:42:20 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/12 22:49:30 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

void execute_pwd(t_shell *shell, t_cmnds *commands)
{
	char dir[MAX_PATH];
	
	if (commands->args[1])
	{
		shell->exit_status = 1;
		write(STDERR_FILENO, "pwd: too many arguments\n", 25);
	}
	else
	{
		shell->exit_status = 0;
		if (getcwd(dir, MAX_PATH) == NULL)
			fatal_error(MLC_ERROR);
		write(STDOUT_FILENO, dir, ft_strlen(dir));
		write(STDOUT_FILENO, "\n", 1);
	}
}