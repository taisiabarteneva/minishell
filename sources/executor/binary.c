/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:32:06 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/22 20:16:44 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_child_exit_status(int *status)
{
	if (WIFEXITED(status))						// не равен нулю, если процесс завершился успешно
		*status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))				// возвращает истинное значение, если дочерний процесс завершился из-за необработанного сигнала
		*status = WTERMSIG(status);
	else if (WIFSTOPPED(status))
		*status = WSTOPSIG(status);				// возвращает истинное значение, если дочерний процесс был остановлен
	else
		*status = EXIT_ERR;
}

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

void c_fork(int signum)
{
	(void)signum;
	write(1, "\n", 1);
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
	signal(SIGINT, (void *)c_fork);
	if (is_built_in(command->args->content))
	{
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

void here_doc(char *del)
{
	char	*line;

	while (true)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strnstr(line, del, ft_strlen(del)) != NULL
			&& ft_strlen(line) == ft_strlen(del) + 1)
			break ;
		write(STDOUT_FILENO, line, ft_strlen(line) + 1);
		free(line);
	}
	exit(EXIT_SUCCESS);
}

int open_files(t_redirs *elem, t_shell *shell, int fd)
{	
	(void)shell;
	if (elem->mode == 0)
	{
		fd = open(elem->filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (fd == -1)
			fatal_error("open\n");
		dup2(fd, STDOUT_FILENO);
	}
	if (elem->mode == 1)
	{
		fd = open(elem->filename, O_RDONLY, 0777);
		if (fd == -1)
		{
			shell->exit_status = 1;
			write(2, "minishell: ", 11);
			write(2, elem->filename, ft_strlen(elem->filename) + 1);
			write(2, ": No such file or directory\n", 28);
		}
		dup2(fd, STDIN_FILENO);
	}
	if (elem->mode == 2)
	{
		fd = open(elem->filename, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (fd == -1)
			fatal_error("open\n");
		dup2(fd, STDOUT_FILENO);
	}
	if (elem->mode == 3)
	{	
		
		here_doc(elem->filename);
	}
	return (fd);
}

int  handle_pipes_redirects(t_cmnds *command, t_shell *shell)
{
	int i;
	int fd = 0;
	
	i = 0;
	while (command->redirs && command->redirs[i])
	{
		fd = open_files(command->redirs[i], shell, fd);
		i++;
	}
	return (fd);
}

void wait_child_processes(int process_count)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (i < process_count)
	{
		wait(&status);
		if (status != 0)
			get_child_exit_status(&status);
		i++;
	}
}

void handle_first_command(t_cmnds *command, t_shell **shell)
{
	int fd_in;
	
	fd_in = handle_pipes_redirects(command, *shell);
	dup2((*shell)->pipes[0][1], STDOUT_FILENO);
	close((*shell)->pipes[0][0]);
}

void handle_last_command(t_cmnds *command, t_shell **shell)
{
	int fd_out;

	fd_out = handle_pipes_redirects(command, *shell);	
	dup2((*shell)->pipes[(*shell)->process_count - 2][0], STDIN_FILENO);
	close((*shell)->pipes[(*shell)->process_count - 2][1]);
}

void	handle_standard_command(t_cmnds *command, t_shell **shell, int cmd_pos)
{
	(void)command;
	dup2((*shell)->pipes[cmd_pos - 1][0], STDIN_FILENO);
	dup2((*shell)->pipes[cmd_pos][1], STDOUT_FILENO);
}

void get_command_position(t_cmnds *command, t_shell **shell, int cmd_pos)
{
	if (cmd_pos == 0)
		handle_first_command(command, shell);
	else if (cmd_pos == (*shell)->process_count - 1)
		handle_last_command(command, shell);
	else
		handle_standard_command(command, shell, cmd_pos);
}

void execute_bin(t_cmnds **commands, t_shell **shell, char **envp)
{
	pid_t	pid;
	int		counter;

	counter = 0;
	while (commands[counter])
	{
		pid = fork();
		if (pid == 0)
		{
			if ((*shell)->process_count > 1)
			{
				get_command_position(commands[counter], shell, counter);
				close_all_pipes((*shell)->pipes);
			}
			handle_pipes_redirects(commands[counter], *shell);
			launch_command(commands[counter], envp, shell);
		}
		else if (pid == -1)
		{
			write(2, "minishell: fork: Resource temporarily unavailable\n", 50);
			(*shell)->exit_status = 128;
			exit(128);			
		}
		counter++;
	}
	close_all_pipes(((*shell)->pipes));
	wait_child_processes((*shell)->process_count);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, (void *)sigint_handler);
}