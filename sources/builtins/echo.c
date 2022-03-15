/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:42:05 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/15 13:34:22 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void execute_echo(char **args, t_shell *shell)
{
	int 	flag;
	int		i;

	i = 1;
	flag = 0;
	if (!args[1])
	{
		write(1, "\n", 1);
		return ;		
	}	
	if (ft_strncmp(args[1], "-n", ft_strlen("-n")) == 0 
		&& ft_strlen("-n") == ft_strlen(args[1]))
		flag = 1;
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		i++;	
	}
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	shell->exit_status = 0;
}