#include "../includes/minishell.h"

char *find_env_node(t_envars *list, const char *key)
{
	t_envars	*tmp;
	char		*value;

	tmp = list;
	value = NULL;
	if (tmp == NULL)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0 
			&& ft_strlen(tmp->key) == ft_strlen(key))
			value = tmp->value;
		tmp = tmp->next;
	}
	return (value);
}

void handle_unset_home(void)
{
	// change exit status
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, "HOME not set\n", 14);
}

void handle_empty_input(t_envars *list)
{
	char		*root_path;
	int			status;

	root_path = find_env_node(list, "HOME");
	status = chdir(root_path);
	if (status == -1)
		handle_unset_home();
}

void handle_non_existing_path(t_cmnds *commands)
{
	// change exit status
	write(STDERR_FILENO, "minishell: cd: ", 15);
	write(STDERR_FILENO, commands->arg, ft_strlen(commands->arg));
	write(STDERR_FILENO, ": No such file or directory\n", 29);
}

void change_old_pwd_environ(t_envars **list, char *old_path)
{
	t_envars	*old_pwd_node;

	old_pwd_node = ft_envar_new("OLD_PWD", old_path);
	if (!old_pwd_node)
		fatal_error(MLC_ERROR);
	ft_envar_del_one(list, "OLDPWD");
	// ft_envar_add_back(list, old_pwd_node);
}

void change_new_pwd_environ(t_envars **list, char *new_path)
{
	t_envars *new_pwd_node;

	new_pwd_node = ft_envar_new("PWD", new_path);
	if (!new_pwd_node)
		fatal_error(MLC_ERROR);
	dprintf(2, "HERE [%s]\n", new_pwd_node->value);
	ft_envar_del_one(list, "PWD");
	// ft_envar_add_back(list, new_pwd_node);
}

void execute_cd(t_envars **list, t_cmnds **commands)
{
	int		status;
	char	old_path[MAX_PATH];
	char	new_path[MAX_PATH];

	// tmp 
	t_cmnds *tmp;
	tmp = *commands;
	if (getcwd(old_path, MAX_PATH) == NULL)
		fatal_error(MLC_ERROR);
	if (tmp->arg == NULL)
		handle_empty_input(*list);
	else 
	{
		status = chdir(tmp->arg);
		if (status == -1)
		{
			handle_non_existing_path(*commands);
		}
	}
	if (getcwd(new_path, MAX_PATH) == NULL)
		fatal_error(MLC_ERROR);
	// change_old_pwd_environ(list, old_path);
	// change_new_pwd_environ(list, new_path);
}


/*
	1. save current path (old_path)
	2. change path (chdir)
	3. handle if path doesn't exist
	4. handle if path is empty
		- find home environ var
		- if no home, throw an error
		- else, cd to home
	5. change OLD_PWD in environ
	6. change PWD in environ
	done, you are perfect
*/