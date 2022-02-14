# include "minishell.h"

/* 
The line readline returns is allocated with malloc (); you should free () the line when you are done with it.
If you want the user to be able to get at the line later, (with C-p for example), 
you must call add_history () to save the line away in a history list of such lines.
add_history (line); 
*/

char *get_line(void)
{
	static char *line_read;
	
	line_read = (char *)NULL;
	if (line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}
	line_read = readline("");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	char *line;
	line = get_line();
	// handle_line();
	// printf("Hello, there will be a minishell soon\n");
	free(line);
	return (0);
}