/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:12:14 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/22 17:47:52 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_pipes(int **pipes)
{
	int	i;

	i = 0;
	while (pipes && pipes[i] != NULL)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void open_pipes(int **pipes, int cmnds)
{
	int i;

	i = 0;
	while (i < cmnds - 1)
	{
		if (pipe(pipes[i]) == -1)
			fatal_error(PIPES_ERR);
		i++;
	}
}

int **pipes_loop(int cmnds)
{
	int		i;
	int		**pipes;
	
	i = 0;
	pipes = (int **)malloc(sizeof(int *) * cmnds);
	// dprintf(2, "CMNDS : [%d]\n", cmnds);
	if (!pipes)
		fatal_error(MLC_ERROR);
	while (i < cmnds - 1)
	{	
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			fatal_error(MLC_ERROR);
		i++;
	}
	// dprintf(2, "I IS : [%d]\n", i);
	pipes[i] = NULL;
	open_pipes(pipes, cmnds);
	return (pipes);
}