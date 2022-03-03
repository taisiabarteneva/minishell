# include "minishell.h"

# define MAXDIR 1024

void execute_pwd(void)
{
	char dir[MAXDIR];

	getcwd(dir, MAXDIR);
	write(STDOUT_FILENO, dir, ft_strlen(dir));
	write(STDOUT_FILENO, "\n", 1);
}

void execute_env(t_env_vars *list)
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

void execute_unset(t_env_vars **list, char *key)
{
	t_env_vars *prev;
	t_env_vars *next;
	t_env_vars *tmp;

	tmp = *list;

	if (tmp && tmp->next)
	{
		while (tmp)
		{
			if (ft_strlen(tmp->key) == ft_strlen(key) 
				&& ft_strncmp((const char *)tmp->key,
				(const char *)key, ft_strlen(key)) == 0)
			{
				prev = tmp->prev;
				if (tmp->next != NULL)
				{
					next = tmp->next;
					next->prev = prev;
				}
				else
					next = NULL;
				prev->next = next;
			}
			if (tmp->next != NULL)
				tmp = tmp->next;
			else
				break ; 
		}
	}
}

void execute_exit(void)
{
	write(STDOUT_FILENO, "exit\n", 5);
	exit(EXIT_SUCCESS);

}

void execute_cd(t_env_vars **list, char *path)
{
	int status;
	(void)list;

	status = chdir(path);
	if (status == -1)
		write(STDERR_FILENO, "No such file or directory\n", 17);
}

void execute_echo(char *line)
{
	int flag;

	// -n option
	flag = 1;
	write(STDOUT_FILENO, line, ft_strlen(line));
	if (flag == 1)
		write(STDOUT_FILENO, "$", 1);
	else if (flag == 0)
		write(STDOUT_FILENO, "\n", 1);
}

void built_ins(char *cmd, t_env_vars **list)
{
	// tmp argument
	char	*path;
	char 	*key;
	char	*line;

	key = "LESS";
	path = "/Users/wurrigon/Desktop";
	line = "hey there";
	if (ft_strncmp((const char *)cmd, "pwd", 3) == 0 &&
		ft_strlen(cmd) == ft_strlen("pwd"))
		execute_pwd();
	else if (ft_strncmp((const char *)cmd, "env", 3) == 0 &&
		ft_strlen(cmd) == ft_strlen("env"))
		execute_env(*list);
	else if (ft_strncmp((const char *)cmd, "unset", 5) == 0 &&
		ft_strlen(cmd) == ft_strlen("unset"))
		execute_unset(list, key);
	else if (ft_strncmp((const char *)cmd, "exit", 4) == 0 &&
		ft_strlen(cmd) == ft_strlen("exit"))
		execute_exit();
	else if (ft_strncmp((const char *)cmd, "cd", 2) == 0 &&
		ft_strlen(cmd) == ft_strlen("cd"))
		execute_cd(list, path);
	else if (ft_strncmp((const char *)cmd, "echo", 4) == 0 &&
		ft_strlen(cmd) == ft_strlen("echo"))
		execute_echo(line);
}