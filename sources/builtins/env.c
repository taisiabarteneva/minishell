/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:41:59 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/16 14:05:47 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void execute_env(t_envars *list, t_shell *shell, t_list *args)
{
	(void)args;
	shell->exit_status = 0;
	while (list)
	{
		write(STDOUT_FILENO, list->key, ft_strlen(list->key));
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, list->value, ft_strlen(list->value));
		write(STDOUT_FILENO, "\n", 1);
		list = list->next;
	}
}