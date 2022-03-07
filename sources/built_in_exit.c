#include "../includes/minishell.h"

void execute_exit(void)
{
	write(STDOUT_FILENO, "exit\n", 5);
	exit(EXIT_SUCCESS);
}