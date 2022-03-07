/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:44:17 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/07 20:09:04 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void *sigint_handler(int sig_num)
{
	(void)sig_num;
	
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	// clear_input();
	return (NULL);
}

void catch_signals(void)
{
	signal(SIGINT, (void *)sigint_handler); // ctrl-c
	signal(SIGQUIT, SIG_IGN); 				// ctrl-/
	signal(SIGTSTP, SIG_IGN); 				// ctrl-z
}
