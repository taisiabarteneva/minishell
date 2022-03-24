/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:32:06 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/24 22:24:07 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sig_heredoc(int sig)
{
	(void)sig;
	exit(EXIT_ERR);
}

void	c_fork(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}

void	launch_command(t_cmnds *command, char **envp, t_shell **shell)
{
	char	*path;
	char	**cmdargs;
	int		exec_res;

	(void)shell;
	path = NULL;
	cmdargs = get_command_arguments(command->args);
	if (!cmdargs)
		fatal_error(MLC_ERROR);
	// signal(SIGINT, (void *)c_fork);
	if (is_built_in(command->args->content))
	{
		built_ins(&(command->envs), command, shell, envp);
		exit(0);		
	}
	else if (ft_strchr(command->args->content, '/') != NULL)
		exec_non_system_bin(command, &path, &cmdargs);
	else
		exec_system_bin(command, &path, &cmdargs);
	// (*shell)->exit_status = 0;
	if (path == NULL && !find_env_node(command->envs, "PATH"))
	{
		(*shell)->exit_status = 127;
		write(STDERR_FILENO, "minishell: ", 11);		
		write(STDERR_FILENO, cmdargs[0], ft_strlen(cmdargs[0]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		exit((*shell)->exit_status);
	}
	else if (path == NULL)
	{
		(*shell)->exit_status = 127;
		write(STDERR_FILENO, "minishell: ", 11);		
		write(STDERR_FILENO, cmdargs[0], ft_strlen(cmdargs[0]));
		write(STDERR_FILENO, ": command not found\n", 20);
		exit((*shell)->exit_status);
	}
	else 
	{	
		(*shell)->exit_status = 0;
		exec_res = execve(path, cmdargs, envp);
		if (exec_res == -1)
		{
			(*shell)->exit_status = 127;
			write(STDERR_FILENO, "minishell: ", 11);		
			write(STDERR_FILENO, cmdargs[0], ft_strlen(cmdargs[0]));
			write(STDERR_FILENO, ": command not found\n", 20);
		}
		if (exec_res == -1 && cmdargs && *cmdargs)
		{
			(*shell)->exit_status = 127;
			write(STDERR_FILENO, "minishell: ", 11);		
			write(STDERR_FILENO, cmdargs[0], ft_strlen(cmdargs[0] + 1));
			write(STDERR_FILENO, ": No such file or directory\n", 28);
			exit((*shell)->exit_status);
		}
	}
	(*shell)->exit_status = EXIT_ERR;
	exit((*shell)->exit_status);
}

void here_doc(char *del, t_shell **shell, int in)
{
	char 	*line;
	int 	fd;

	(void)shell;
	(*shell)->exit_status = 0;
	fd = open("/tmp/file",  O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		
		fatal_error("open\n");
	}
	while (true)
	{
		line = get_next_line(in);
		if (!line)
			break ;
		if (ft_strncmp(del, line, ft_strlen(del)) == 0
			&& ft_strlen(del) == ft_strlen(line) - 1)
			break;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	fd = open("/tmp/file", O_RDONLY, 0777);
	if (fd == -1)
		fatal_error("open\n");
	dup2(fd, STDIN_FILENO);
}

int open_files(t_redirs *elem, t_shell **shell, int fd, int in, t_redirs *next)
{	
	(void)next;
	if (elem->mode == 0)
	{
		fd = open(elem->filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (fd == -1)
		{
			(*shell)->exit_status = 2;			
			fatal_error("open\n");
		}
		dup2(fd, STDOUT_FILENO);
	}
	if (elem->mode == 1)
	{
		fd = open(elem->filename, O_RDONLY, 0777);
		if (fd == -1)
		{
			(*shell)->exit_status = 1;
			write(2, "minishell: ", 11);
			write(2, elem->filename, ft_strlen(elem->filename) + 1);
			write(2, ": No such file or directory\n", 28);
			// if (!next)
				exit(1);
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
		signal(SIGINT, (void *)ft_sig_heredoc);
		here_doc(elem->filename, shell, in);
	}
	return (fd);
}

int  handle_pipes_redirects(t_cmnds *command, t_shell **shell, int in)
{
	int i;
	int fd = 0;
	
	i = 0;
	while (command->redirs && command->redirs[i])
	{
		open_files(command->redirs[i], shell, fd, in, command->redirs[i + 1]);
		i++;
	}
	return (fd);
}

void	ft_fork(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void execute_bin(t_cmnds **commands, t_shell **shell, char **envp, int in)
{
	pid_t	pid;
	int		counter;

	counter = 0;
	(*shell)->exit_status = 0;
	while (commands[counter])
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, (void *)ft_sig_heredoc);
			if ((*shell)->process_count > 1)
			{
				get_command_position(commands[counter], shell, counter, in);
				close_all_pipes((*shell)->pipes);
			}
			else
				handle_pipes_redirects(commands[counter], shell, in);
			launch_command(commands[counter], envp, shell);
		}
		else if (pid == -1)
			fork_error(shell);
		counter++;
	}
	// unlink("tmp");
	close_all_pipes(((*shell)->pipes));
	wait_child_processes(shell, pid);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, (void *)sigint_handler);
}