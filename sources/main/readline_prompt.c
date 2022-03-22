/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:23:49 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/22 13:56:38 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_line_to_history(char *line)
{
	if (line && *line)
		add_history(line);
}

void	set_shell(t_envars **envs, t_shell **shell, char **envp)
{
	char	*line;
	t_cmnds	**commands;
	int		i;
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
		i = -1;
		commands = ft_parse_input(line, *envs);
		if (*line != '\0')
		{
			while (commands && commands[++i])
			{
				in = dup(0);
				out = dup(1);
				if (is_built_in(commands[0]->args->content) && !commands[1])
				{
					handle_pipes_redirects(commands[i], *shell);		
					built_ins(&(commands[i]->envs), commands[i], *shell, envp);
				}
				else
				{
					execute_bin(commands[i], shell, envp);
				}
				dup2(in, 0);
				dup2(out, 1);
			}
		}
		ft_commands_clear(&commands);
		free(line);
}
}
