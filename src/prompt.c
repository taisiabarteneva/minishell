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

void	set_prompt(char **av, t_env_vars **list)
{
	char 		*line;
	// t_storage 	store;
	(void)av;

	// ======== tmp struct ========= 
	// store.fd_in = av[1];
	// store.cmd = av[1];
	// store.cmd2 = av[3];
	// store.fd_out = av[4];
	// =============================

	line = NULL;
	while (1)
	{
		line = read_prompt_line();
		if (!line)
			break ;
		/* 
			PARSER:
			returns a struct (list of linked lists or a tree) 
		*/
		/*
			EXECUTE HERE
		*/
		// if something do built ins
			built_ins(line, list);
		add_line_to_history(line);
		free(line);
	}
	exit(EXIT_SUCCESS);
}