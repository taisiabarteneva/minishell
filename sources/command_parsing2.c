/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarob <ncarob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:27:27 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/07 18:39:39 by ncarob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_cmnds	*ft_parse_commands(char *str)
// {
// 	t_cmnds	*command;
// 	t_cmnds	*commands_list;
// 	char	**command_blocks;

// 	commands_list = NULL;
// 	command_blocks = ft_split(str, '|');
// 	if (!command_blocks)
// 		return (NULL);
// 	while (*command_blocks)
// 	{

// 	}
// }

// t_cmnds	*ft_command_new(char *str)
// {
// 	t_cmnds	*command;
// 	int		i;
// 	int		j;

// 	command = (t_cmnds *)malloc(sizeof(t_cmnds));
// 	if (!command)
// 		return (NULL);
// 	i = -1;
// 	while (str && str[++i] && (str[i] != ' ' || str[i] != '<' || str[i] != '>'))
// 		;
// 	j = i;
// 	command->command = ft_substr(str, 0, i);
// 	if (str && str[++j] && str[j] == '-')
// 		while (str && str[++j]
// 			&& (str[j] != ' ' || str[j] != '<' || str[j] != '>'))
// 			;
// 	command->flag = ft_substr(str, j, j - i);
// 	command->next = NULL;
// 	return (command);
// }

void	ft_command_add_back(t_cmnds **commands_list, t_cmnds *new_command)
{
	t_cmnds	*copy;

	copy = *commands_list;
	if (!(*commands_list))
	{
		new_command->next = *commands_list;
		*commands_list = new_command;
	}
	else
	{
		while (copy->next)
			copy = copy->next;
		copy->next = new_command;
		new_command->next = NULL;
	}
}

void	ft_cmnds_clear(t_cmnds **commands_list)
{
	t_cmnds	*prev;

	if (!(*commands_list))
		return ;
	prev = NULL;
	while (*commands_list)
	{
		prev = (*commands_list);
		(*commands_list) = (*commands_list)->next;
		if (prev)
		{
			free(prev->outfile);
			free(prev->command);
			free(prev->infile);
			free(prev->flag);
			while (prev->args)
			{
				free(*(prev->args));
				prev->args++;
			}
			free(prev);
		}
	}
	*commands_list = NULL;
}
