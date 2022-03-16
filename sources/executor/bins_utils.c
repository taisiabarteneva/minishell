/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bins_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:09:53 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/16 20:09:09 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **get_command_arguments(t_list *args)
{
	t_list	*curr;
	char 	**cmd_args;
	int		quan;
	int		i;
	
	i = 0;
	curr = args;
	quan = get_args_quantity(args);
	cmd_args = (char **)malloc(sizeof(char *) * (quan + 1));
	if (!cmd_args)
		fatal_error(MLC_ERROR);
	while (i < quan)
	{
		cmd_args[i] = ft_strdup(curr->content);
		if (!cmd_args[i])
			fatal_error(MLC_ERROR);
		curr = curr->next; 
		i++;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}