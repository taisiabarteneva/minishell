#include "../includes/minishell.h"

void execute_pwd(void)
{
	char dir[MAXDIR];

	getcwd(dir, MAXDIR);
	write(STDOUT_FILENO, dir, ft_strlen(dir));
	write(STDOUT_FILENO, "\n", 1);
}