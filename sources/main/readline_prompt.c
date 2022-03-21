/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:23:49 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/21 20:12:04 by wurrigon         ###   ########.fr       */
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
	int		lol = dup(1);
	int		lol2 = dup(0);

	line = NULL;
	commands = NULL;
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
		i = -1;
		commands = ft_parse_input(line, *envs);
		if (*line != '\0')
		{
			while (commands && commands[++i])
			{
				if (is_built_in(commands[0]->args->content) && !commands[1])
				{
					lol = handle_pipes_redirects(commands[i], *shell);		
					built_ins(&(commands[i]->envs), commands[i], *shell, envp);
					dup2(lol, STDOUT_FILENO);
				}
				else
					execute_bin(commands[i], shell, envp);
				dup2(lol, STDOUT_FILENO);
				dup2(lol2, STDIN_FILENO);
			}
		}
		ft_commands_clear(&commands);
		free(line);
}
}
