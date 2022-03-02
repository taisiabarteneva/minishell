# include "minishell.h"

char *read_prompt_line(void)
{
	static char *line_read;
	
	line_read = (char *)NULL;
	if (line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}
	line_read = readline("minishell> ");
	return (line_read);
}

void add_line_to_history(char *line)
{
	if (line && *line)
		add_history(line);
}

void	set_prompt(void)
{
	char 		*line;

	line = NULL;
	while (1)
	{
		line = read_prompt_line();
		if (!line)
			break ;
		add_line_to_history(line);
		free(line);
	}
	exit(EXIT_SUCCESS);
}