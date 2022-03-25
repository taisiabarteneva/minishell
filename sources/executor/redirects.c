/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 22:39:32 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/24 22:43:31 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_left_redir(t_redirs *elem, t_shell **shell)
{
	int	fd;

	fd = open(elem->filename, O_RDONLY, 0777);
	if (fd == -1)
	{
		(*shell)->exit_status = 1;
		write(2, "minishell: ", 11);
		write(2, elem->filename, ft_strlen(elem->filename) + 1);
		write(2, ": No such file or directory\n", 28);
		exit(EXIT_ERR);
	}
	dup2(fd, STDIN_FILENO);
}

void	handle_right_redir(t_redirs *elem, t_shell **shell)
{
	int	fd;

	fd = open(elem->filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		(*shell)->exit_status = 2;
		fatal_error("open\n");
	}
	dup2(fd, STDOUT_FILENO);
}

void	open_files(t_redirs *elem, t_shell **shell, int in)
{	
	int	fd;

	if (elem->mode == 0)
		handle_right_redir(elem, shell);
	if (elem->mode == 1)
		handle_left_redir(elem, shell);
	if (elem->mode == 2)
	{
		fd = open(elem->filename, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (fd == -1)
			fatal_error("open\n");
		dup2(fd, STDOUT_FILENO);
	}
	if (elem->mode == 3)
	{
		signal(SIGINT, (void *)sig_heredoc);
		here_doc(elem->filename, shell, in);
	}
}

int	handle_redirects(t_cmnds *command, t_shell **shell, int in)
{
	int	i;

	i = 0;
	while (command->redirs && command->redirs[i])
	{
		open_files(command->redirs[i], shell, in);
		i++;
	}
	return (0);
}
