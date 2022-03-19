/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:23:49 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/19 21:41:05 by wurrigon         ###   ########.fr       */
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

	line = NULL;
	commands = NULL;
	// rl_outstream = stderr;
	while (true)
	{
		line = readline("minishell> ");
		if (!line)
		{
			write(STDERR_FILENO, "exit\n", 5);
			exit(EXIT_ERR);
		}
		add_line_to_history(line);
		i = -1;
		commands = ft_parse_input(line, *envs);
		if (*line != '\0')
		{
			while (commands && commands[++i])
			{
				execute_command(commands[i], shell, envp);	
			}
		}
		ft_commands_clear(&commands);
		free(line);
	}
}
