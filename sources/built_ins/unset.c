/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:42:26 by wurrigon          #+#    #+#             */
/*   Updated: 2022/03/12 21:41:28 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool is_valid_env_name(const char *str)
{
	while (*str != '\0')
	{
		if (!ft_isalnum(*str) && *str != '+' && *str != '*')
			return (false);
		str++;
	}
	return (true);
}

void execute_unset(t_envars **list, char **args, t_shell *shell)
{
	while (args && *args)
	{
		if (is_valid_env_name(*args) == false)
		{
			shell->exit_status = EXIT_ERR;
			write(STDERR_FILENO, "minishell: unset: `", 19);
			write(STDERR_FILENO, *args, ft_strlen(*args));
			write(STDERR_FILENO, "': not a valid identifier\n", 27);
		}
		else
		{
			ft_envar_del_one(list, *args);
			shell->exit_status = 0;
		}
		args++;
	}
}