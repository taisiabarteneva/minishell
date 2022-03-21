/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:32:06 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/21 20:12:16 by wurrigon         ###   ########.fr       */
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
			fatal_error(MLC_ERROR);
		if (access(*path, F_OK))
			*path = NULL;
	}
	free(paths);
}

void	exec_non_system_bin(t_cmnds *command, char **path, char ***cmdargs)
{
	*cmdargs = ft_split(command->args->content, ' ');
	if (!*cmdargs)
		fatal_error(MLC_ERROR);
	*path = (*cmdargs)[0];
}

void launch_command(t_cmnds *command, char **envp, t_shell **shell)
{
	char	*path;
	char	**cmdargs;

	(void)shell;

	path = NULL;
	cmdargs = get_command_arguments(command->args);
	if (!cmdargs)
		fatal_error(MLC_ERROR);
	if (is_built_in(command->args->content))
	{
		// dprintf(2, "HERE\n");
		built_ins(&(command->envs), command, *shell, envp);
		exit(0);		
	}
	else if (ft_strchr(command->args->content, '/') != NULL)
		exec_non_system_bin(command, &path, &cmdargs);
	else
		exec_system_bin(command, &path, &cmdargs);
	(*shell)->exit_status = 127;
	if (path == NULL && !find_env_node(command->envs, "PATH"))
	{
		write(STDERR_FILENO, "minishell: ", 11);		
		write(STDERR_FILENO, cmdargs[0], ft_strlen(cmdargs[0]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		exit((*shell)->exit_status);
	}
	else if (path == NULL)
	{
		write(STDERR_FILENO, "minishell: ", 11);		
		write(STDERR_FILENO, cmdargs[0], ft_strlen(cmdargs[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		exit((*shell)->exit_status);
	}
	else 
	{	
		(*shell)->exit_status = 0;
		if (execve(path, cmdargs, envp) == -1)
		{
			write(STDERR_FILENO, "minishell: ", 11);		
			write(STDERR_FILENO, cmdargs[0], ft_strlen(cmdargs[0] + 1));
			write(STDERR_FILENO, ": No such file or directory\n", 28);
			exit(1);
		}
	}
	(*shell)->exit_status = EXIT_ERR;
	free(cmdargs);
	free(path);
	exit((*shell)->exit_status);
}

int open_files(t_redirs *elem, t_shell *shell)
{
	int		fd;
	
	int lol = dup(1);
	(void)shell;
	// shell->fd_in = 0;
	// shell->fd_out = 1;
	if (elem->mode == 0)
	{
		fd = open(elem->filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (fd == -1)
			fatal_error("open");
		dup2(fd, STDOUT_FILENO);
	}
	if (elem->mode == 1)
	{
		fd = open(elem->filename, O_RDONLY, 0777);
		if (fd == -1)
			fatal_error("open");
		dup2(fd, STDIN_FILENO);
	}
	if (elem->mode == 2)
	{
		fd = open(elem->filename, O_CREAT | O_RDWR | O_APPEND, 0777);
		if (fd == -1)
			fatal_error("open");
		dup2(fd, STDOUT_FILENO);
	}
	if (elem->mode == 3)
	{
		fd = open(elem->filename, O_CREAT | O_RDWR | O_APPEND, 0777);
		if (fd == -1)
			fatal_error("open");
		dup2(fd, STDIN_FILENO);
	}
	close(fd);
	return (lol);
}

int  handle_pipes_redirects(t_cmnds *command, t_shell *shell)
{
	int i;
	int lol;
	i = 0;
	while (command->redirs[i])
	{
		// dprintf(2, "[%s] [%d]\n", command->redirs[i]->filename, command->redirs[i]->mode);
		lol = open_files(command->redirs[i], shell);
		i++;
	}
	return (lol);
}


void execute_bin(t_cmnds *command, t_shell	**shell, char **envp)
{
	pid_t	pid;
	// int		status;
	int		out;

	pid = fork();
	if (pid == 0)
	{	
		out = handle_pipes_redirects(command, *shell);
		launch_command(command, envp, shell);
		// dup2(out, STDOUT_FILENO);
	}
	else if (pid == -1)
		fatal_error(FORK_ERR);
	else if (pid > 0)
	{
		// if (waitpid(-1, &status, 0) == -1)
		// 	fatal_error(WAITPID_ERR);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, (void *)sigint_handler);
	}
}
// ✗  "echo test > ls >> ls >> ls ; echo test >> ls ; cat ls" 