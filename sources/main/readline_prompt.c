/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:23:49 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/22 20:30:23 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_line_to_history(char *line)
{
	if (line && *line)
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
		if (commands)
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
