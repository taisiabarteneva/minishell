/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:42:05 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/24 21:08:43 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int echo_side(t_list *curr)
{
	int i;
	int flag;

	flag = 0;

	i = 0;
	while (ft_strncmp(curr->content, "-n", ft_strlen("-n")) == 0 
		&& ft_strlen("-n") == ft_strlen(curr->content))
	{
		curr = curr->next;
		flag = 1;
	}
	while (curr)
	{
		if (curr->content && (((char *)curr->content)[0]) && i++)
				write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, curr->content, ft_strlen(curr->content));
		curr = curr->next;
	}
	return (flag);
}

void execute_echo(t_list *args, t_shell **shell)
{
	int 	flag;
	t_list	*curr;

	curr = args->next;
	if (!curr && (*shell)->exit_status != 1)
	{
		write(1, "\n", 1);
		return ;
	}
	else if (!curr)
		return ; 
	flag = echo_side(curr);
	if (!flag)
		write(STDOUT_FILENO, "\n", 1);
	(*shell)->exit_status = 0;
}