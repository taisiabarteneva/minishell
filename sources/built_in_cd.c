#include "../includes/minishell.h"

void execute_cd(t_envars **list, char *path)
{
	int status;

	(void)list;
	status = chdir(path);
	if (status == -1)
		write(STDERR_FILENO, "No such file or directory\n", 17);
}