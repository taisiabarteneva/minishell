/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:41:52 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/13 13:36:34 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_args_quantity(char **args)
{
	int i = 0;
	while (args[i++])
		;
	return (i);
}

bool is_numeric(const char *str) 
{
    while (*str != '\0')
    {
        if (*str < '0' || *str > '9')
            return (false);
        str++;
    }
    return (true);
}

void execute_exit(t_shell *shell, t_cmnds *commands)
{
	write(STDERR_FILENO, "exit\n", 5);
	if (commands->args[1])
	{
		if (commands->args[1] && get_args_quantity(commands->args) != 1)
		{
			write(STDERR_FILENO, "minishell: exit: ", 17);
			write(STDERR_FILENO, commands->args[0], ft_strlen(commands->args[0]));
			write(STDERR_FILENO, "too many arguments\n", 20);
			shell->exit_status = EXIT_ERR;
		}
		else if (commands->args[1] && is_numeric(commands->args[1]) == false)
		{
			write(STDERR_FILENO, "minishell: exit: ", 17);
			write(STDERR_FILENO, commands->args[0], ft_strlen(commands->args[0]));
			write(STDERR_FILENO, "numeric argument required\n", 26);
			shell->exit_status = 255;
			exit(shell->exit_status);
		}
		else if (ft_atoi(commands->args[1]) > 255)
			exit(ft_atoi(commands->args[1]) % 256);
	}
	else
	{
		shell->exit_status = 0;
		exit(shell->exit_status);
	}
	exit(shell->exit_status);
}