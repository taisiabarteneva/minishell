/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:44:17 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/24 22:47:51 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigquit_handler(int num)
{
	(void)num;
	write(2, "Quit: 3\n", 8);
	exit(131);
}

void	*sig_fork(int num)
{
	(void)num;
	write(1, "\n", 1);
	exit(2);
}

void	set_signals(void)
{
	signal(SIGINT, (void *)sig_fork);
	signal(SIGQUIT, (void *)sigquit_handler);
}

void	return_signals_parent_process(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
