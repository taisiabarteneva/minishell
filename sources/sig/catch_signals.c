/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:44:17 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/10 19:53:44 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int tcgetattr(int fd, struct termios *termios_p) -  получить параметры, связанные с объектом, 
// на который ссылается fd, и сохранить их в структуре termios, на которую ссылается termios_p. 
// int tcsetattr(int fd, int optional_actions, struct termios *termios_p) - меняет параметры, связанные с терминалом

void tty_hide_input(void)
{
	struct termios term;
	
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL; // terminal special characters other than TAB, NL, START, and STOP are echoed as ^X
	tcsetattr(STDIN_FILENO, 0, &term);
}

void *sigint_handler(int sig_num)
{
	(void)sig_num;
	
	// tty_hide_input();
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return (NULL);
}

void catch_signals(void)
{
	signal(SIGINT, (void *)sigint_handler); // ctrl-c
	signal(SIGQUIT, SIG_IGN); 				// ctrl-/
	signal(SIGTSTP, SIG_IGN); 				// ctrl-z
}
