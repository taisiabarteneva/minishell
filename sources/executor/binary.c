/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:32:06 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/24 22:57:56 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_empty_path(char *path, t_cmnds *command, char **cmdargs,
		t_shell **shell)
{
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
}

void	my_exec(t_shell **shell, char *path, char **cmdargs, char **envp)
{
	int	exec_res;

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

void	launch_command(t_cmnds *command, char **envp, t_shell **shell)
{
	char	*path;
	char	**cmdargs;

	path = NULL;
	cmdargs = get_command_arguments(command->args);
	if (!cmdargs)
		fatal_error(MLC_ERROR);
	if (is_built_in(command->args->content))
	{
		built_ins(&(command->envs), command, shell, envp);
		exit(0);
	}
	else if (ft_strchr(command->args->content, '/') != NULL)
		exec_non_system_bin(command, &path, &cmdargs);
	else
		exec_system_bin(command, &path, &cmdargs);
	handle_empty_path(path, command, cmdargs, shell);
	my_exec(shell, path, cmdargs, envp);
	(*shell)->exit_status = EXIT_ERR;
	exit((*shell)->exit_status);
}

pid_t	watch_child_process(t_shell **shell, t_cmnds **commands, int in,
		char **envp)
{
	int		counter;
	pid_t	pid;

	counter = 0;
	set_signals();
	while (commands[counter])
	{
		pid = fork();
		if (pid == 0)
		{
			if ((*shell)->process_count > 1)
			{
				get_command_position(commands[counter], shell, counter, in);
				close_all_pipes((*shell)->pipes);
			}
			else
				handle_redirects(commands[counter], shell, in);
			launch_command(commands[counter], envp, shell);
		}
		else if (pid == -1)
			fork_error(shell);
		counter++;
	}
	return_signals_parent_process();
	return (pid);
}

void	execute_bin(t_cmnds **commands, t_shell **shell, char **envp, int in)
{
	pid_t	pid;
	int		counter;

	counter = 0;
	(*shell)->exit_status = 0;
	pid = watch_child_process(shell, commands, in, envp);
	close_all_pipes(((*shell)->pipes));
	wait_child_processes(shell, pid);
}
