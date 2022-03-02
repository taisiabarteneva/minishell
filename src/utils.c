# include "minishell.h"

void fatal_error(char *msg)
{
    write(STDERR_FILENO, msg, ft_strlen(msg));
    exit(EXIT_FAILURE);
}
