#include "../includes/minishell.h"

void execute_echo(t_cmnds *commands)
{
	write(STDOUT_FILENO, *(commands->args), ft_strlen(*(commands->args)));
	if (commands->flag)
		write(STDOUT_FILENO, "$", 1);
	else if (!commands->flag)
		write(STDOUT_FILENO, "\n", 1);
}	