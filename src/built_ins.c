# include "minishell.h"

void execute_pwd(t_env_vars *list)
{
	if (list && list->next)
	{
		while (list)
		{
			if (ft_strlen((const char *)list->key) == 6 
				&& ft_strncmp((const char *)list->key, "OLDPWD", 6) == 0)
				break ;
			list = list->next;
		}
		if (list->value)
		{
			write(STDOUT_FILENO, list->value, ft_strlen(list->value));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
}

void execute_env(t_env_vars *list)
{
	if (list && list->next)
	{
		while (list)
		{
			write(STDOUT_FILENO, list->key, ft_strlen(list->key));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, list->value, ft_strlen(list->value));
			write(STDOUT_FILENO, "\n", 1);
			list = list->next;
		}
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

void built_ins(char *cmd, t_env_vars **list)
{
	// tmp argument
	char 	*key;

	key = "_";
	if (ft_strncmp((const char *)cmd, "pwd", 3) == 0)
		execute_pwd(*list);
	else if (ft_strncmp((const char *)cmd, "env", 3) == 0)
		execute_env(*list);
	else if (ft_strncmp((const char *)cmd, "unset", 5) == 0)
		execute_unset(list, key);
	else if (ft_strncmp((const char *)cmd, "exit", 4) == 0)
		execute_exit();
}