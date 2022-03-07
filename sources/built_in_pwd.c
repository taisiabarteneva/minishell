#include "../includes/minishell.h"

void execute_pwd(void)
{
	char dir[MAX_PATH];

	if (getcwd(dir, MAX_PATH) == NULL)
		fatal_error(MLC_ERROR);
	write(STDOUT_FILENO, dir, ft_strlen(dir));
	write(STDOUT_FILENO, "\n", 1);
}