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

/*
----------
int tcgetattr(int fd, struct termios *termios_p) -  получить параметры,
связанные с объектом, на который ссылается fd, и сохранить их в структуре
termios, на которую ссылается termios_p. 
------------------
int tcsetattr(int fd, int optional_actions, struct termios *termios_p)
- меняет параметры, связанные с терминалом.
----------
*/

void	tty_hide_input(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, 0, &term);
}

void	*sigint_handler(int sig_num)
{
	(void)sig_num;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return (NULL);
}

void	catch_signals(void)
{
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	sig_heredoc(int sig)
{
	(void)sig;
	exit(EXIT_ERR);
}

void	c_fork(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}
