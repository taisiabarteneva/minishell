/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:32:06 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/18 01:37:15 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	get_child_exit_status(int *status)
// {
// 	if (WIFEXITED(status))						// не равен нулю, если процесс завершился успешно
// 		*status = WEXITSTATUS(status);
// 	else if (WIFSIGNALED(status))				// возвращает истинное значение, если дочерний процесс завершился из-за необработанного сигнала
// 		*status = WTERMSIG(status);
// 	else if (WIFSTOPPED(status))
// 		*status = WSTOPSIG(status);				// возвращает истинное значение, если дочерний процесс был остановлен
// 	else
// 		*status = EXIT_ERR;
// }

char **parse_paths(t_envars *list)
{
	char	**my_paths;	
	char	*path_env;
	int		i;
	
	i = 0;
	path_env = find_env_node(list, "PATH");
	if (!path_env)
		return (NULL);
	my_paths = ft_split(path_env, ':');
	if (!my_paths)
		fatal_error(MLC_ERROR);
	while (my_paths[i])
	{
		my_paths[i] = ft_strjoin(my_paths[i], "/", 0, 0);
		if (!my_paths[i])
			fatal_error(MLC_ERROR);
		i++;
	}
	return (my_paths);
}

void exec_system_bin(t_cmnds *command, char **path, char ***cmd_args)
{
	char	**paths;
	int		i;

	i = 0;
	paths = parse_paths(command->envs);
	*cmd_args = get_command_arguments(command->args);
	if (!(*cmd_args))
		fatal_error(MLC_ERROR);
	while (paths && paths[i])
	{
		*path = ft_strjoin(paths[i], (*cmd_args)[0], 0, 0);
		if (!*path)
			fatal_error(MLC_ERROR);
		if (access(*path, F_OK) == 0)
			break ;
		free(paths[i]);
		free(*path);
		*path = NULL;
		i++;
	}
	if (!*path)
	{
		*path = ft_strjoin("/", (*cmd_args)[0], 0, 0);
		if (!*path)
			fatal_error("malloc");
		if (access(*path, F_OK))
			*path = NULL;
	}
	free(paths);
}

int launch_command(t_cmnds *command, char **envp, t_shell **shell)
{
	char	*path;
	char	**cmdargs;

	(void)shell;

	path = NULL;
	cmdargs = get_command_arguments(command->args);
	if (!cmdargs)
		fatal_error(MLC_ERROR);
	exec_system_bin(command, &path, &cmdargs);
	(*shell)->exit_status = 127;
	if (path == NULL && !find_env_node(command->envs, "PATH"))
	{
		write(STDERR_FILENO, "minishell: ", 11);		
		write(STDERR_FILENO, cmdargs[0], ft_strlen(cmdargs[0]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		exit(127);
	}
	else if (path == NULL)
	{
		write(STDERR_FILENO, "minishell: ", 11);		
		write(STDERR_FILENO, cmdargs[0], ft_strlen(cmdargs[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		exit((*shell)->exit_status);
	}
	else 
	{	(*shell)->exit_status = 0;
		if (execve(path, cmdargs, envp) == -1)
			fatal_error(EXEC_ERROR);
	}
	(*shell)->exit_status = EXIT_ERR;
	exit((*shell)->exit_status);
}


void execute_bin(t_cmnds *command, t_shell	**shell, char **envp)
{
	pid_t	pid;
	int		status;

	(void)command;
	(void)envp;
	
	pid = fork();
	if (pid == 0)
	{	
		launch_command(command, envp, shell);          	// child process 
	}
	else if (pid == -1)
		fatal_error(FORK_ERR);     						// handle error
	else if (pid > 0)
	{
		if (waitpid(-1, &status, 0) == -1)
			fatal_error(WAITPID_ERR);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, (void *)sigint_handler);
	}
}
