# include "minishell.h"

typedef struct s_struct
{
	char *infile;
	char *cmd1;
	char *operator;
	char *cmd2;
	char *outfile;
}				t_struct;

t_struct *handle_line(char *line)
{
	t_struct 	*storage;
	char 		**splitted_line;

	storage = (t_struct *)malloc(sizeof(t_struct));
	if (!storage)
	{
		printf("Malloc error\n");
		exit(1);
	}
	memset(storage, 0, sizeof(t_struct));
	splitted_line = ft_split(line, ' ');
	storage->infile = splitted_line[0];
	storage->cmd1 = splitted_line[1];
	storage->operator = splitted_line[2];
	storage->cmd2 = splitted_line[3];
	storage->outfile = splitted_line[4];
	free(splitted_line);
	return (storage);
}

char *read_prompt_line(void)
{
	static char *line_read;
	
	line_read = (char *)NULL;
	if (line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}
	line_read = readline("happyminishell> ");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

int	init_shell(void)
{
	char 		*line;
	t_struct 	*storage;

	line = NULL;
	while (1)
	{
		line = read_prompt_line();
		if (!line)
			break ;
		/* parser */
		storage = handle_line(line);
		free(storage);
		free(line);
	}
	return (1);
}

int main(int ac, char **av, char **ev)
{
	(void)av;
	(void)ev;

	if (ac != 1)
	{
		ft_putendl_fd("Usage: ./minishell", STDOUT_FILENO);
		return (0);
	}
	if (init_shell() == 1)
	{
		ft_putendl_fd("Malloc error", STDERR_FILENO);
		exit(1);
		// return (1);
	}
	return (0);
}