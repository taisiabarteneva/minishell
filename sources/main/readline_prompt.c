/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:23:49 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/24 13:02:30 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_line_to_history(char *line)
{
	if (line && *line && *line != ' ')
		add_history(line);
}

int get_num_of_commands(t_cmnds **commands)
{
	int i;

	i = 0;
	while (commands && commands[i])
		i++;
	return (i);
}

bool	check_tabs_spaces(char *content)
{
	int i;
	i = 0;
	while (content[i])
	{
		if (content[i] != 8 && content[i] != 9)
			return false;
		i++;
	}
	return (true);
}

void	set_shell(t_envars **envs, t_shell **shell, char **envp)
{
	char	*line;
	t_cmnds	**commands;
	int		in, out;

	line = NULL;
	commands = NULL;
	rl_outstream = stderr;
	catch_signals();
	while (true)
	{
		tty_hide_input();
		line = readline("minishell> ");
		if (!line)
		{
			write(STDERR_FILENO, "exit\n", 5);
			exit(EXIT_ERR);
		}
		else
			add_line_to_history(line);
		commands = ft_parse_input(line, *envs, *shell);
		if (commands && check_tabs_spaces((*commands)->args->content) == false)
		{
			(*shell)->process_count = get_num_of_commands(commands);
			if ((*shell)->process_count > 1)
			{
				(*shell)->pipes = pipes_loop((*shell)->process_count);
			}
			if (*line != '\0')
			{
				in = dup(0);
				out = dup(1);
				if (is_built_in(commands[0]->args->content) && !commands[1])
				{
					handle_pipes_redirects(commands[0], *shell);
					built_ins(&(commands[0]->envs), commands[0], *shell, envp);
				}
				else
					execute_bin(commands, shell, envp);
				dup2(in, 0);
				dup2(out, 1);
			}
		}
		// (void)in;
		// (void)out;
		// (void)envp;
		ft_commands_clear(&commands);
		free(line);
	}
}
