/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 18:23:49 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/07 20:00:58 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*read_prompt_line(void)
{
	static char	*line_read;

	line_read = NULL;
	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	line_read = readline("minishell> ");
	return (line_read);
}

void	add_line_to_history(char *line)
{
	if (line && *line)
		add_history(line);
}

void	set_prompt(t_envars **envs)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = read_prompt_line();
		if (!line)
			break ;
		else
		{
			ft_parse_input(line, *envs);
			// do_something();
			// ft_cmds_clear(&comnds);
		}
		add_line_to_history(line);
		free(line);
	}
	exit(EXIT_SUCCESS);
}
