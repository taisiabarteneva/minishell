/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:41:52 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/18 01:44:47 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_args_quantity(t_list *args)
{
	int 		i;
	t_list		*tmp;

	i = 0;
	tmp = args;
	while (tmp)
	{
		i++;
		tmp = tmp->next;	
	}
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

void execute_exit(t_shell *shell, t_list *args)
{
	write(STDERR_FILENO, "exit\n", 5);
	if (args->next)
	{
		if (get_args_quantity(args) != 2)
		{
			write(STDERR_FILENO, "minishell: exit: ", 17);
			write(STDERR_FILENO, args->content, ft_strlen(args->content));
			write(STDERR_FILENO, " too many arguments\n", 20);
			shell->exit_status = EXIT_ERR;
		}
		else if (is_numeric(args->next->content) == false)
		{
			write(STDERR_FILENO, "minishell: exit: ", 17);
			write(STDERR_FILENO, args->next->content, ft_strlen(args->next->content));
			write(STDERR_FILENO, " numeric argument required\n", 28);
			shell->exit_status = 255;
			exit(shell->exit_status);
		}
		else if (is_numeric(args->next->content) == true)
			exit(ft_atoi(args->next->content) % 256); // check
	}
	else
	{
		shell->exit_status = 0;
		exit(shell->exit_status);
	}
	exit(shell->exit_status);
}