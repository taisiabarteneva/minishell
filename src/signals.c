#include <minishell.h>

// SIGINT - прерывание процесса (Ctrl-C) - gives prompt back, exit status 130
// SIGQUIT - выход из процесса (Ctrl-\) - does nothing, exit status 0
// SIGSTP - остановка процесса (Ctrl-Z) - does nothing (in bash), exit status 0

// void (*signal(int signal_num, void (*handler)(int)))(int)
// signal_num - id сигнала (например, SIGTERM)
// handler - указатель на функцию-обработчик сигнала


// In Bash:
// SIGINT is caught and handled
// In all cases, Bash ignores SIGQUIT. If job control 
// is in effect (see Job Control), Bash ignores SIGTTIN, SIGTTOU, and SIGTSTP.

// Function: int rl_on_new_line ()
// Tell the update functions that we have moved onto a new (empty) line, 
// usually after ouputting a newline.

// Function: void rl_replace_line (const char *text, int clear_undo)
// Replace the contents of rl_line_buffer with text. The point and mark are preserved, 
// if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.

void *sigint_handler(int sig_num)
{
	(void)sig_num;

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
