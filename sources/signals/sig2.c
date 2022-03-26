/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:32:06 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/24 22:57:56 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigquit_handler(int num)
{
	(void)num;
	write(1, "Quit: 3\n", 8);
	exit(3);
}

void	*sig_fork(int num)
{
	(void)num;
	exit(2);
}

void	set_signals(t_cmnds **commands)
{
	if (ft_strncmp(commands[0]->args->content, "cat", ft_strlen("cat")) == 0)
		signal(SIGQUIT, (void *)sigquit_handler);
	signal(SIGINT, (void *)sig_fork);
	signal(SIGQUIT, sigquit_handler);
}

void	return_signals_parent_process(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
