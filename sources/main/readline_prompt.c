/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:23:49 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/24 22:48:35 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_line_to_history(char *line)
{
	if (line && *line && *line != ' ')
		add_history(line);
}

int	get_num_of_commands(t_cmnds **commands)
{
	int	i;

	i = 0;
	while (commands && commands[i])
		i++;
	return (i);
}

bool	check_tabs_spaces(char *content)
{
	int		i;

	i = 0;
	while (content[i])
	{
		if (content[i] != SPACE && content[i] != TAB)
			return (false);
		i++;
	}
	return (true);
}

void	execute_command(t_cmnds **commands, t_shell **shell, char **envp,
			char *line)
{
	int	in;
	int	out;

	if (commands && check_tabs_spaces((*commands)->args->content) == false)
	{
		(*shell)->process_count = get_num_of_commands(commands);
		if ((*shell)->process_count > 1)
			(*shell)->pipes = pipes_loop((*shell)->process_count);
		if (*line != '\0')
		{
			in = dup(STDIN_FILENO);
			out = dup(STDOUT_FILENO);
			if (is_built_in(commands[0]->args->content) && !commands[1])
			{
				handle_redirects(commands[0], shell, in);
				built_ins(&(commands[0]->envs), commands[0], shell, envp);
			}
			else
				execute_bin(commands, shell, envp, in);
			dup2(in, STDIN_FILENO);
			dup2(out, STDOUT_FILENO);
		}
	}
}

void	set_shell(t_envars **envs, t_shell **shell, char **envp)
{
	char	*line;
	t_cmnds	**commands;

	commands = NULL;
	(*shell)->pipes = NULL;
	rl_outstream = stderr;
	while (true)
	{
		tty_hide_input();
		catch_signals();
		line = readline("minishell> ");
		if (!line)
		{
			write(STDERR_FILENO, "exit\n", 5);
			exit(EXIT_ERR);
		}
		add_line_to_history(line);
		commands = ft_parse_input(line, *envs, *shell);
		execute_command(commands, shell, envp, line);
		ft_commands_clear(&commands);
		free(line);
	}
}
