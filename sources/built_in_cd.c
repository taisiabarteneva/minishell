#include "../includes/minishell.h"

void handle_empty_input(t_envars *list)
{
	char		*root_path;
	int			status;
	t_envars	*tmp;

	tmp = list;
	root_path = NULL;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		if (tmp && tmp->key == "HOME")
			root_path = tmp->value;
		tmp = tmp->next;
	}
	if (root_path)
	{
		status = chdir(root_path);
		if (status == -1)
			handle_unset_home();
	}
}

void handle_non_existing_path(t_cmnds *commands)
{
	// exit status
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, commands->arg, ft_strlen(commands->arg));
	write(STDERR_FILENO, ": No such file or directory\n", 29);
}

void change_pwd_environ()
{
	
}

void execute_cd(t_envars **list, t_cmnds **commands)
{
	int		status;
	char	*old_path;
	char	*new_path;

	// tmp 
	t_cmnds *tmp;
	tmp = *commands;
	
	// save current path
	if (getcwd(old_path, MAX_PATH) == NULL)
		fatal_error(MLC_ERROR);
	// change path
	status = chdir(tmp->arg);
	if (tmp->args[0] == NULL)
	{
		handle_empty_input(*list);
	}
	if (status == -1)
	{
		handle_non_existing_path(*commands);
	}
	// save new current path
	if (getcwd(new_path, MAX_PATH) == NULL)
		fatal_error(MLC_ERROR);
	// update paths in environment
	change_pwd_environ();
}


/*
	1. save current path
	2. change path
	3. handle if path doesn't exist
	4. handle if path is empty
		- find home environ var
		- if no home, throw an error
		- else, cd to home
	5. change OLD_PWD in environ
	6. change PWD in environ
	done, you are perfect
*/