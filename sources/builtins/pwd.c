/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:42:20 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/24 20:58:53 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void execute_pwd(t_shell **shell, t_list *args, t_envars *list)
{
	char dir[MAX_PATH];
	char *tmp_dir;

	if (args->next)
	{
		(*shell)->exit_status = 1;
		write(STDERR_FILENO, "pwd: too many arguments\n", 25);
	}
	else
	{
		(*shell)->exit_status = 0;
		if (getcwd(dir, MAX_PATH) == NULL)
		{
			tmp_dir = find_env_node(list, "OLD_PWD");
			write(1, tmp_dir, ft_strlen(tmp_dir) + 1);
		}
		write(STDOUT_FILENO, dir, ft_strlen(dir));
		write(STDOUT_FILENO, "\n", 1);
	}
}