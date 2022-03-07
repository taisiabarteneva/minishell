#include "../includes/minishell.h"

void execute_env(t_envars *list)
{
	if (list == NULL)
		exit(EXIT_FAILURE); // what to do in case of null envp
	while (list)
	{
		write(STDOUT_FILENO, list->key, ft_strlen(list->key));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, list->value, ft_strlen(list->value));
		write(STDOUT_FILENO, "\n", 1);
		list = list->next;
	}
}